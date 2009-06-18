
class QtlMarker
  attr_reader :name, :chromosome, :position, :mid

  def initialize name, chromosome, position, mid
    @name = name
    @chromosome = chromosome
    # Convert position to a number, when applicable
    position = position.to_f if (position.to_f.to_s == position)
    position = position.to_i if (position.to_i.to_s == position)
    @position = position
    @mid = mid
  end
end

# Markers are stored by marker name. Use QtlMap to get an ordered
# set of markers.

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
  def [] name
    return @data[name] if @data[name]
    # name not recognized, try by mid
    by_id(name)
  end

end
