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

  >> na_in = FastaReader.new(NA_FILE)
  >> na_in.each { | record | p record }
  => true

  >> na_out = FastaWriter.new("na.fa")
  >> aa_out = FastaWriter.new("aa.fa")


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
