# FastaReader
#

class FastaReader

  def initialize fn, opts={:regex => '(\S+)'}
    @f = File.open(fn)
    @regex = opts[:regex]
    if opts[:index]
      # indexer
    end
    @curr_line = @f.gets
  end

  def each
    # rewind file
    @f.seek 0
    begin
      tag = @curr_line
      tag =~ /^>/
      descr = $'.strip
      descr =~ /#{@regex}/
      id = $1
      seq = ""
      begin
        line = @f.gets
        break if line =~ /^>/
        seq += line.strip 
      end while !@f.eof 
      @curr_line = line
      yield FastaRecord.new(id, descr, seq)
    end while !@f.eof
  end

  def close
    @f.close
  end
end
