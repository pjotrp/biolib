
class FastaRecord
  attr_accessor :id, :descr, :seq

  def initialize id, descr, seq
    @id = id
    @descr = descr
    @seq = seq
  end
end

class FastaPairedRecord
  attr_reader :na, :aa

  def initialize na, aa
    @na = na
    @aa = aa
    raise "ID error NA #{na.id} not matching AA #{aa.id}" if na.id != aa.id
    raise "Sequence size mismatch for #{na.id}" if na.seq.size != aa.seq.size*3
  end

  def id
    @aa.id
  end
end
