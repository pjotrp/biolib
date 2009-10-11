
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
  end

  def id
    @aa.id
  end
end
