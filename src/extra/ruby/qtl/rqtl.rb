# RQTL convenience wrapper for Biolib R/QTL mappings

require 'biolib/rqtl'

class RQTL

  def initialize qtl
    @qtl = qtl
  end

  # Calls directly into R/QTL the scanone method with options and returns
  # a list of markers with chromosome positions and lod scores.

  def scanone options

    # call the C function
    if (:method == "mr" or :method=="mr-imp" or :method=="mr-argmax")
=begin
       z <- .C("R_scanone_mr",
              as.integer(n.ind),         # number of individuals
              as.integer(n.pos),         # number of markers
              as.integer(n.gen),         # number of possible genotypes
              as.integer(newgeno),       # genotype data
              as.double(ac),       # additive covariates
              as.integer(n.ac),
              as.double(ic),       # interactive covariates
              as.integer(n.ic),
              as.double(pheno),          # phenotype data
              as.double(weights),        # weights
              result=as.double(rep(0,n.pos)),
              PACKAGE="qtl")
=end
      res = Biolib::rqtl.R_scanone_mr()
    end
  end

end
