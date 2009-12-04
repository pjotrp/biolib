
require 'biolib/biolib_core'

module GenericAdaptor
  include Contract

  def method_missing method, *args
    if @adapted.respond_to? method
      @adapted.send(method, *args)
    else
      raise NotImplementedError 'Method missing in interface!'
    end
  end
end

module RQtlMap
  GMAP = { 'A' => 1, 'H' => 2, 'B' => 3, 'C' => 4, 'D' => 5, '-' => 'NA', 'NA' => 'NA' }
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
    # FIXME multiple phenotypes 
    phs = @adaptedphenotypes.to_a.flatten
    inds.collect { | i | phs[i] }
  end

  # Create a genotype matrix, as used by R/qtl. Optionally pass in 
  # the individuals  and (expanded) markers. 
  # The method fetches through the genotype(ind,mar) method
  # which should return NA when no data available and reduce the ambiguous
  # genotypes for an experimental type (RIL, F2, BC).
  def scanone_ingenotypematrix individuals=nil, markers=nil
    if individuals != nil
      inds = individuals.index
    else
      inds = use_individuals 
    end
    contract("No inds") { inds!=nil and inds.size > 0 }
    markers = @adapted.markers if !markers
    # all genotype information is stored in a flat array for scanone.
    # These are accessed as Geno[j][i] where j=marker an i=individual
    markers_size = markers.size
    inds_size    = inds.size
    m_size = inds_size*markers_size 
    g_array = Array.new.fill(-127,0..m_size-1)
    inds.each_with_index do | ind, i |
      markers.each_with_index do | m, j |
        g_array[j*inds_size+i] = genotype(ind,j)
      end
    end
    m = g_array
    # p [markers.size, inds.size, m_size]
    # p m[0..4]
    # (0..4).each { |i|  p [m[i],m[markers.size+i],m[2*markers.size+i]] }
    contract("Dimension #{m.size} != #{m_size}") {  m.size == m_size }
    contract("Array not fully initialized") { !m.include?(-127) }
    m
  end

  def genotype ind, mar
    contract("F2 only") { @adapted.type==:f2 }
    g = super(ind,mar)
    contract("no nils") { g!=nil }
    # FIXME in case of mr with RIL
    # zero all NA's
    g = 0 if g=='NA' 
    g = 0 if g>3
    g
  end

  def weights
    Biolib::Biolib_core.biolib_log(7,"weights are fixed at 1.0")
    ws = Array.new.fill(1.0,0..use_individuals.size-1)
    ws
  end

  # return index of used individuals (helper method)
  def use_individuals(dropna = true)
    inds = []
    # test for valid phenotypes
    # FIX multiple phenotypes and NA's (now zeroed)
    phs = @adaptedphenotypes.to_a.flatten
    phs.each_with_index do | ph, i |
      if dropna
        inds.push i if ph != 'NA'
      else
        inds.push
      end
    end
    inds
  end

end
