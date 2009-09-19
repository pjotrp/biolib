# Ruby DocTest
#
# Run with ./runner.rb or
#
#   ../../../../tools/rubydoctest/bin/rubydoctest test_fasta.rb
#
# Documentation with rd2 -r rd/rd2html-lib *.rb

cwd = File.dirname(__FILE__)
Dir.chdir(cwd)

$: << '../../../mappings/swig/ruby/rqtl/'
$: << '../../../mappings/swig/ruby/biolib_core/'
$: << '../../../mappings/swig/ruby/biolib_R/'

require 'biolib/biolib_core'

Biolib::Biolib_core.biolib_setloglevel(7)

if $UNITTEST

=begin

  >> $: << '..'
  >> require 'db/fasta'
  >> TESTDIR = '../../../test/data/fasta'
  >> NA_FILE = TESTDIR + "/na.fa"
  >> AA_FILE = TESTDIR + "/aa.fa"

BioLib's reference FASTA reader and writer contain a number of useful properties.
First RAM usage is limited. Second the interface is simple and to the point.

Open a reader and walk the file to find a FASTA record

  >> na_in = FastaReader.new(NA_FILE)
  >> fastarec = nil
  >> na_in.each { | rec | fastarec = rec if rec.id =~ /-Arabidopsis_thaliana-126/ }
  >> fastarec.id
  => "PUT-157a-Arabidopsis_thaliana-126"

Open a writer and write the record

  >> na_out = FastaWriter.new("na.fa")
  >> na_out.write fastarec
  >> na_out.close

Cleanup 

  >> File.unlink("na.fa")

The ID in the FASTA file can vary between implementations. Therefore a regex is
allowed to find the ID - the default is /^(\S+)/ - or the first non-white space
making up the tag. Here we grab the first relevant number

  >> na_in = FastaReader.new(NA_FILE, :regex => '(\d+)\s')
  >> na_in.each { | rec | fastarec = rec if rec.id == "126" }
  >> fastarec.id
  => "126"

In the first examples the FastaReader parses the whole file on demand. When
we use the :index option an indexer is built up at the same time (or the 
first time an indexing function is used). So

  >> na_in = FastaReader.new(NA_FILE, :regex => '(\d+)\s', :index => true)
  >> rec = na_in.get("122")
  >> rec.id
  => "122"

Fetching more information from the FASTA file does not parse the whole file
again

  >> na_in.get("121").id
  => "121"
  >> na_in.get("121").seq
  => "CAATTTTTTAAACATTTACTGGTTACTAAATTTGGAGATAGTATCACATTTCTAAAGGGTAAGTTGGAAAATAAATTTACAGAAAAATTATAAGTATAAAAAGTATACAGATGGATTACTTAGACAGCAGCGGGTGTGGGGGCTGATGCGGAGTGGTCGTGGTCGAAGAAGGAACCCGGTTTCCGGGGGGATCTCAGTAAACTCGGAAAGAATGGCCCGAATTCGTCACCGCCAACTAGTTCTTCCTCGAGAAGCACTTCAACGAGCTTATCATGGGCTTCACGATTGTTCTTTATGTGGGTTAGAGCTATCTCATATGCACTGGCTGATAGTTTCTTCACCGGCAGAATCAATGTCTTCTGGAAGCTTCTCAGAAATGGAGTTTCTTGGCACCATCCT"

=end


$: << '..'
require 'db/fasta'
require 'test/unit'

TESTDIR = '../../../test/data/fasta'
NA_FILE = TESTDIR + "/na.fa"
AA_FILE = TESTDIR + "/aa.fa"

class TestBiolibFasta < Test::Unit::TestCase

  def setup
  end

  def test_indexer
    na_in = FastaReader.new(NA_FILE, :regex => '(\d+)\s', :index => true)
    rec = na_in.get("122")
    assert_equal("122",rec.id)
    assert_equal("121",na_in.get("121").id)
  end

end

end # $UNITTEST
