# RQTL convenience wrapper for Biolib R/QTL mappings

require 'biolib/rqtl'

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
=end
      d = @qtl.data
      # p d
      # res = Biolib::Rqtl.scanone_mr(d.nind,d.totmar,5,geno,[],0,[],0,pheno,[])
    end
    res
  end

  def scanone_mr
    scanone(:method=>'mr')
  end

end
