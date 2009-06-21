# RQTL convenience wrapper for Biolib R/QTL mappings

require 'biolib/rqtl'
require 'biolib/biolib_R'

class RQTL

  include Contract

  def initialize qtl
    @qtl = qtl
  end

  def expand_markers! step
    step_width = :fixed
    off_end = 0
    contract("step > 0") { step>0 }
    contract("off_end == 0") { off_end == 0 }
    @qtl.data.expand_markers!(2.5)
  end

=begin

  Simulate from the joint distribution Pr(g | O) using default values for
  error.prob, off.end, stepwidth and map function.

     z <- .C(sim_geno_f2,
              as.integer(n.ind),         # number of individuals
              as.integer(n.pos),         # number of markers
              as.integer(n.draws),       # number of simulation replicates
              as.integer(newgen),        # genotype data
              as.double(rf),             # recombination fractions
              as.double(error.prob),     # 
              draws=as.integer(rep(0,n.draws*n.ind*n.pos)), 
              PACKAGE="qtl")

=end

  def sim_geno n_draws
    error_prob = 0.0001
    map_function = :haldane
    contract("error_prob") {  error_prob>0 and error_prob<1 }
    contract("F2 only") { @qtl.data.type==:f2 }

    Biolib::Biolib_R.BioLib_R_Init()
    r = RQtlScanoneAdaptor.new(@qtl.data)
    d = @qtl.data
    map = d.map # marker map (expanded)

    # calculate frequencies one chromosome at a time since we have to expand 
    # the markers
    Biolib::Biolib_core.biolib_log(7,"sim all markers by chromosome")
    draws = []
    Biolib::Biolib_core.biolib_log(7,"sim Haldane freq. only; ignores X")
    d.chromosomes.names.each do | chromosome |
      p [chromosome,map.markers(chromosome).size,n_draws,map.recombination_fractions(chromosome).size]
      # draws is an DIM3 array of n_ind x n_mar x n_draws Draws[repl][mar][ind]
 
      ds    = Biolib::Rqtl.sim_geno_f2(d.individuals.size,
                                       map.markers(chromosome).size,
                                       n_draws,
                                       r.scanone_ingenotypematrix(d.individuals,map.markers),
                                       map.recombination_fractions(chromosome)+[-127.0],
                                       error_prob)
      p [chromosome,ds.size]
      contract("Mismatch in size") { ds.size == 48000 if chromosome == '1'}
      draws += ds
    end
    return n_draws, draws
  end

  # Calls directly into R/QTL the scanone method with options and returns
  # a list of markers with chromosome positions and lod scores.

=begin
       z <- .C("R_scanone_mr",
              as.integer(n.ind),         # number of individuals
              as.integer(n.pos),         # number of markers
              as.integer(n.gen),         # number of possible genotypes
              as.integer(newgeno),       # genotype data
              as.double(ac),             # additive covariates
              as.integer(n.ac),
              as.double(ic),             # interactive covariates
              as.integer(n.ic),
              as.double(pheno),          # phenotype data
              as.double(weights),        # weights
              result=as.double(rep(0,n.pos)),
              PACKAGE="qtl")

 * scanone_mr: Performs genome scan using marker regression.
 * n_ind        Number of individuals
 * n_pos        Number of marker positions
 * n_gen        Number of different genotypes
 * Geno         Genotype matrix
 * Addcov       Matrix of additive covariates: Addcov[cov][ind]
 * n_addcov     Number of columns of Addcov
 * Intcov       Number of interactive covariates: Intcov[cov][ind]
 * n_intcov     Number of columns of Intcov
 * pheno        Phenotype data, as a vector
 * weights      Vector of positive weights, of length n_ind
 * result       Vector of length n_pos, to contain the RSS
 *
 **********************************************************************/

void scanone_mr(int n_ind, int n_pos, int n_gen, int **Geno,
    double **Addcov, int n_addcov, double **Intcov,
    int n_intcov, double *pheno, double *weights,
    double *result);

=end

  def scanone options
    Biolib::Biolib_R.BioLib_R_Init()
    res = nil
    # call the C function
    if (options[:method] == "mr" or options[:method]=="mr-imp" or options[:method]=="mr-argmax")
      result = [] # place holder
      r = RQtlScanoneAdaptor.new(@qtl.data)
      # p [r.scanone_ingenotypematrix]
      # p [r.weights]
      # p [r.use_individuals.size, r.scanone_inphenotypevector.size]
      # p [r.markers.size, r.scanone_ingenotypematrix.size, r.weights.size]
      res = Biolib::Rqtl.scanone_mr(r.use_individuals.size,
                                    r.markers.size,
                                    r.genotypes.names.size,
                                    r.scanone_ingenotypematrix,
                                    r.addcov,
                                    r.naddcov,
                                    r.intcov,
                                    r.nintcov,
                                    r.scanone_inphenotypevector,
                                    r.weights) 
    elsif (options[:method] == "imp")
      n_draws, draws = options[:sim_geno]
      p [n_draws, draws.size]
      r = RQtlScanoneAdaptor.new(@qtl.data)
      # p [r.scanone_ingenotypematrix]
      # p [r.weights]
      # p [r.use_individuals.size, r.scanone_inphenotypevector.size]
      # p [r.markers.size, r.scanone_ingenotypematrix.size, r.weights.size]

=begin
void scanone_imp(int n_ind, int n_pos, int n_gen, int n_draws,
                 int ***Draws, double **Addcov, int n_addcov,
                 double **Intcov, int n_intcov, double *pheno,
                 int nphe, double *weights,
                 double **Result)
=end

      contract_warn("Dim of draw #{draws.size} rather then #{r.use_individuals.size * r.markers.size * n_draws}") { draws.size == r.use_individuals.size * r.markers.size * n_draws }

      map = @qtl.data.map
      contract("No map") { map != nil }
      res = Biolib::Rqtl.scanone_imp(r.use_individuals.size,
                                    map.markers.size,
                                    r.genotypes.names.size,
                                    n_draws,
                                    draws,
                                    r.scanone_ingenotypematrix(nil,map.markers),
                                    r.addcov,
                                    r.naddcov,
                                    r.intcov,
                                    r.nintcov,
                                    r.scanone_inphenotypevector,
                                    r.use_individuals.size,
                                    r.weights) 
    end
    ro = RQtlScanoneOutputAdaptor.new(r)
    ro.results(res)
  end

  def scanone_mr
    scanone(:method => 'mr')
  end

  def scanone_imp sim_geno
    scanone(:method => 'imp',:sim_geno => sim_geno)
  end

end
