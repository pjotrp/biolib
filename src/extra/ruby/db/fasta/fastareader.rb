# FastaReader
#

require 'db/fasta/indexer'

class FastaReader

  include Indexer

  def initialize fn, opts={:regex => '(\S+)'}
    @f = File.open(fn)
    @fread_once = false
    @regex = opts[:regex]
    indexer_use opts[:index]
  end

  def parse_each
    @f.seek 0    # force file rewind
    @rec_fpos = 0
    @rec_line = @f.gets
    fpos = 0
    begin
      # digest id from record description
      id, descr = digest_tag(@rec_line)
      id_fpos = @rec_fpos
      # parse the sequence
      seq = ""
      begin
        fpos = @f.tell
        line = @f.gets
        break if line =~ /^>/
        seq += line.strip 
      end while !@f.eof 
      # new record
      @rec_fpos = fpos
      @rec_line = line
      # p [@rec_line, id, id_fpos]
      indexer_set id, id_fpos if @indexer and !@fread_once
      yield id, descr, seq
    end while !@f.eof
    @fread_once = true
  end

  # returns a FastaRecord for every item
  def each
    parse_each { | id, descr, seq | yield FastaRecord.new(id, descr, seq) }
  end

  # Return a record by its +id+, nil when not found
  def get id
    if @indexer and !@fread_once
      # force indexer
      # $stderr.print "Force indexer"
      parse_each { | x, y, z | nil }
    end
    if fpos = indexer_get(id)
      get_rec(fpos)
    else
      nil
    end
  end

  def get_rec fpos
    @f.seek fpos
    tag = @f.gets
    seq = ""
    begin
      line = @f.gets
      break if line =~ /^>/
      seq += line.strip 
    end while !@f.eof
    id, descr = digest_tag(tag)
    FastaRecord.new(id,descr,seq)
  end
  
  def digest_tag tag
    tag =~ /^>/
    descr = $'.strip
    descr =~ /#{@regex}/
    id = $1
    return id, descr
  end

  def close
    @f.close
  end
end
