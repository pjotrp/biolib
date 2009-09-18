# Fasta writer

class FastaWriter

  def initialize fn
    @f = File.open(fn,"w")
  end

  def write descr, seq
    @f.write "> ",desrc,"\n"
    @f.write seq.strip, "\n"
  end

end
