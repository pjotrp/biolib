# Storage object for a result

class QtlResult
  attr_reader :marker, :lod

  def initialize marker, lod
    @marker = marker
    @lod = lod
  end

  def name
    @marker.name
  end

  def chromosome
    @marker.chromosome
  end

  def position
    @marker.position
  end

  def to_a
    [name,chromosome,position,lod]
  end

  def pretty
    format("%-20s\t%3s\t%.3f\t%.6f\n",name,chromosome,position,lod)
  end

end


