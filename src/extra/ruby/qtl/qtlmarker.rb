
class QtlMarker
  attr_reader :name, :chromosome, :position, :mid

  def initialize name, chromosome, position, mid
    @name = name
    @chromosome = chromosome
    @position = position
    @mid = mid
  end
end

# Markers are stored has by marker name
class QtlMarkers 

  def initialize 
    @data = {}
  end

  def set name, chromosome, pos, mid=nil
    @data[name] = QtlMarker.new(name, chromosome, pos, mid)
  end

  def each 
    @data.each do | k,v |
      yield v
    end
  end

  def by_id mid
    each do | m |
      return m if m.mid == mid
    end
    nil
  end

  def size
    @data.size
  end

  # Find marker by name, or by index
  def []
    @data[name]
  end

end
