class QTLChromosomes

  # Chromosomes are not actually stored separately, this is a helper class. From 
  # an object models perspective this is not logical (chromosomes have markers),
  # but from a QTL analysis perspective the marker is the starting point.

  def initialize markers
    @markers = markers
  end

  def chromosomes
    chr = {}
    @markers.each do | marker |
      chr[marker.chromosome] = 0 if !chr[marker.chromosome]
      chr[marker.chromosome] += 1
    end
    chr
  end

  def hasX?
    chromosomes['X'] != nil
  end

  def size
    chromosomes.size
  end

  def autosomes
    res = chromosomes.reject {|k,v| k=='X'}
    # size - (hasX? ? 1:0)
    res
  end

  def markers
    @markers
  end
end
