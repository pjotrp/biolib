
class FastaRecord
  attr_accessor :id, :descr, :seq

  def initialize id, descr, seq
    @id = id
    @descr = descr
    @seq = seq
  end
end
