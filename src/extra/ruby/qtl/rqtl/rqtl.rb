# RQTL convenience wrapper for Biolib R/QTL mappings

require 'biolib/rqtl'
require 'biolib/biolib_R'

class RQTL

  def initialize qtl
    @qtl = qtl
  end

  # Calls directly into R/QTL the scanone method with options and returns
  # a list of markers with chromosome positions and lod scores.

  def scanone options
    res = nil
    # call the C function
    if (options[:method] == "mr" or options[:method]=="mr-imp" or options[:method]=="mr-argmax")
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
      result = [] # place holder
      r = RQtlInputAdaptor.new(@qtl.data)
      res = Biolib::Rqtl.scanone_mr(r.individuals.size,
                                    r.markers.size,
                                    r.genotypes.names.size,
                                    r.genotypematrix,
                                    r.addcov,
                                    r.naddcov,
                                    r.intcov,
                                    r.nintcov,
                                    r.phenotypevector,
                                    r.weights)
    end
    res
  end

  def scanone_mr
    scanone(:method=>'mr')
  end

end
