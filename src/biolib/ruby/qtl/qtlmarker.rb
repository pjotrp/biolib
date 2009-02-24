
class QtlMarker
  attr_reader :name, :chromosome, :position

  def initialize name, chromosome, position 
    @name = name
    @chromosome = chromosome
    @position = position
  end
end
