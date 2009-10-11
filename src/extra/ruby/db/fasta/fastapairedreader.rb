# FASTA paired reader keeps track of two FASTA files containing
# matching NA and AA sequences.
#

class FastaPairedReader

  def initialize nafn, aafn, opts={:regex => '(\S+)'}
    @na = FastaReader.new(nafn, opts)
    @aa = FastaReader.new(aafn, opts)
  end

end
