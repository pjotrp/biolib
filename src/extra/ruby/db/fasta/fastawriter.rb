# Fasta writer

class FastaWriter

  # Open a FASTA stream for writing
  def initialize fn
    @f = File.open(fn,"w")
  end

  # write a FASTA item
  def write item
    @f.write "> ",item.descr,"\n"
    @f.write item.seq.strip, "\n"
  end

  def close
    @f.close
  end

end
