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

Open a writer and write the record

  >> na_out = FastaWriter.new("na.fa")
  >> na_out.write fastarec
  >> na_out.close

Cleanup 

  >> File.unlink("na.fa")

=end


$: << '..'
require 'db/fasta'
require 'test/unit'

class TestBiolibFasta < Test::Unit::TestCase

  def setup
  end

  def test_info
  end

end

end # $UNITTEST
