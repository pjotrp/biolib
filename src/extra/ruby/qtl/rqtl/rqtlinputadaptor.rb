
require 'biolib/biolib_core'

module GenericAdaptor
  def method_missing method, *args
    if @adapted.respond_to? method
      @adapted.send(method, *args)
    else
      raise NotImplementedError 'Method missing in interface!'
    end
  end
end

module RQtlMap
  GMAP = { 'A' => 1, 'H' => 2, 'B' => 3, 'C' => 4, 'D' => 5, '-' => 'NA' }
  NAMAP = { '-' => 'NA', 'NA' => 'NA' }

  def gtranslate g
    return GMAP[g] if g
    g
  end

  def natranslate n
    return 'NA' if n==nil
    return NAMAP[n] if n
    n
  end
end

class RQtlGenotypesAdaptor
  include GenericAdaptor, RQtlMap

  def initialize adapted
    @adapted = adapted
  end

  def names
    @adapted.names.collect { | n | gtranslate(n) }
  end

  def alleles
    @adapted.alleles.collect { | n | gtranslate(n) }
  end

  def na
    @adapted.na.collect { | n | natranslate(n) }
  end

  def to_matrix
    raise "undefined"
  end
end

class RQtlPhenotypesAdaptor
  include GenericAdaptor, RQtlMap

  def initialize adapted
    @adapted = adapted
  end

  def na
    @adapted.na.collect { | n | natranslate(n) }
  end

  def to_a
    @adapted
  end

end

class RQtlInputAdaptor 
  include GenericAdaptor, RQtlMap

  def initialize qtldataset
    @adapted = qtldataset 
    @adaptedgenotypes = RQtlGenotypesAdaptor.new(qtldataset.genotypes)
    @adaptedphenotypes = RQtlPhenotypesAdaptor.new(qtldataset.phenotypes)
  end

  def genotype ind, mar
    gtranslate(@adapted.genotype(ind,mar))
  end

  def genotypes
    @adaptedgenotypes
  end

  def phenotypes
    @adaptedphenotypes
  end

end


class RQtlScanoneAdaptor < RQtlInputAdaptor

  # return phenotypes for use by scanone function
  def scanone_inphenotypevector
    inds = use_individuals
    # FIX multiple phenotypes 
    phs = @adaptedphenotypes.to_a.flatten
    inds.collect { | i | phs[i] }
  end

  def scanone_ingenotypematrix
    inds = use_individuals
    gmatrix = Array.new.fill(-127,0..inds.size*@adapted.markers.size-1)
    inds.each_with_index do | ind, idx |
      (0..@adapted.markers.size-1).each do | mar |
        # gmatrix[idx*@adapted.markers.size+mar] = genotype(ind,mar)
        gmatrix[mar*inds.size+idx] = genotype(ind,mar)
      end
    end
    # m = gmatrix.to_a.flatten.collect { | g | (g=='NA' ? 0:g) }
    m = gmatrix
    # p m
    # contracts:
    raise "Dimension error" if m.size != inds.size*@adapted.markers.size
    raise "Contents error" if m.include?(-127)
    m
  end

  def genotype ind, mar
    g = super(ind,mar)
    # FIXME in case of mr with RIL
    # zero all NA's
    g = 0 if g=='NA' or g==nil 
    g = 0 if g>3
    g
  end

  def weights
    ws = Array.new.fill(1.0,0..use_individuals.size-1)
    ws
  end

  def recombinationfractions
    Biolib::Biolib_core.biolib_log(1,"rfs not set")
  end

  # return index of used individuals
  def use_individuals
    inds = []
    # test for valid phenotypes
    # FIX multiple phenotypes and NA's (now zeroed)
    phs = @adaptedphenotypes.to_a.flatten
    phs.each_with_index do | ph, i |
      inds.push i if ph != 'NA'
    end
    inds
  end

end
