# FastaReader
#

require 'db/fasta/indexer'

class FastaReader

  include Indexer

  def initialize fn, opts={:regex => '(\S+)'}
    @f = File.open(fn)
    @regex = opts[:regex]
    indexer_use opts[:index]
    @curr_line = @f.gets
  end

  def parse_each
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
      yield id, descr, seq
    end while !@f.eof
  end

  # returns a FastaRecord for every item
  def each
    parse_each { | id, descr, seq | yield FastaRecord.new(id, descr, seq) }
  end

  def close
    @f.close
  end
end
