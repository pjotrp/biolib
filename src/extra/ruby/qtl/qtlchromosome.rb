
module QtlChromosomeTests

  XNAME = 'X'

  def isX? name
    name == XNAME
  end
end


class QtlChromosomes

  include QtlChromosomeTests

  # Chromosomes are not actually stored separately, this is a helper class. From 
  # an object models perspective this is not logical (chromosomes have markers),
  # but from a QTL analysis perspective the marker is the starting point.

  def initialize markers
    @markers = markers
  end

  def hasX?
    chromosomes[XNAME] != nil
  end

  def size
    chromosomes.size
  end

  def autosomes
    res = chromosomes.reject {|k,v| k==XNAME}
    # size - (hasX? ? 1:0)
    res
  end

  def markers
    @markers
  end

  def each
    chromosomes.each do | chromosome |
      yield chromosome
    end
  end

  def chromosomes
    chr = {}
    @markers.each do | marker |
      chr[marker.chromosome] = 0 if !chr[marker.chromosome]
      chr[marker.chromosome] += 1
    end
    chr
  end

  def names
    chromosomes.collect { | k, v | k }
  end

  # Return the number of markers per chromosome
  def nmar
    chr = {}
    @markers.each do | marker |
      chr[marker.chromosome] = 0 if !chr[marker.chromosome]
      chr[marker.chromosome] += 1
    end
    chr
  end

end
