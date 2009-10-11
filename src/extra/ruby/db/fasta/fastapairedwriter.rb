# Paired FASTA writer (tracks matching NA and AA sequences in two
# FASTA files)
#

class FastaPairedWriter

  def initialize nafn, aafn
    @na = FastaWriter.new(nafn)
    @aa = FastaWriter.new(aafn)
  end

  def write rec
    @na.write rec.na
    @aa.write rec.aa
  end

  def close
    @na.close
    @aa.close
  end
end
