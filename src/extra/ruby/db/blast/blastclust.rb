# Parse BLAST cluster file
#

class BlastClust

  def initialize fn
    @fn = fn
  end

  def each
    File.new(@fn).each_line do | line |
      yield line.split
    end
  end

end
