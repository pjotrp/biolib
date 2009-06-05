
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

  def genotypematrix
    gmatrix = Array.new.fill(0.0,0..@adapted.individuals.size*@adapted.markers.size)
    (0..@adapted.individuals.size-1).each do | ind |
      (0..@adapted.markers.size-1).each do | mar |
        gmatrix[ind*@adapted.markers.size+mar] = genotype(ind,mar)
      end
    end
    p gmatrix
    gmatrix.to_a.flatten.collect { | g | (g=='NA' ? 0:g) }
  end

  def phenotypevector
    # FIX multiple phenotypes and NA's (now zeroed)
    @adaptedphenotypes.to_a.flatten.collect { | ph | (ph=='NA' ? 0:ph) }
  end

  def weights
    []
  end
end
