# FASTA paired reader keeps track of two FASTA files containing
# matching NA and AA sequences.
#

class FastaPairedReader

  def initialize nafn, aafn, opts={:regex => '(\S+)'}
    @na = FastaReader.new(nafn, opts)
    @aa = FastaReader.new(aafn, opts)
  end

  # return a NA+AA pair
  def get id
    na = @na.get(id)
    aa = @aa.get(id)
    FastaPairedRecord.new(na, aa)
  end

end
