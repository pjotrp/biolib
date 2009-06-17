# RQTL convenience wrapper for Biolib R/QTL mappings

require 'biolib/rqtl'
require 'biolib/biolib_R'

class RQTL

  def initialize qtl
    @qtl = qtl
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

  def sim_geno step, n_draws
    error_prob = 0.0001
    off_end = 0
    map_function = :haldane
    step_width = :fixed

    Biolib::Biolib_R.BioLib_R_Init()
    r = RQtlScanoneAdaptor.new(@qtl.data)
    draws = Biolib::Rqtl.sim_geno_f2(r.use_individuals.size,
                                     r.markers.size,
                                     n_draws,
                                     r.scanone_ingenotypematrix,
                                     r.recombinationfractions,
                                     error_prob)
    draws
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
    end
    ro = RQtlScanoneOutputAdaptor.new(r)
    ro.results(res)
  end

  def scanone_mr
    scanone(:method => 'mr')
  end

  def scanone_imp gp
    scanone(:method => 'imp',:gp => gp)
  end

end
