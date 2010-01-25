# Ruby DocTest for MQM
#
# Run with ./runner.rb or
#
#   ../../../../tools/rubydoctest/bin/rubydoctest test_rqtl_mqm.rb
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

Like with the R/qtl scanone example we load the R/qtl Listeria dataset (from a CSV).

  >> $: << '..'
  >> require 'qtl/rqtl'

Locate the Listeria input file
 
  >> DIR = '../../../test/data/qtl'
  >> LISTERIA  = DIR+'/listeria.csv'
  >> File.exist?(LISTERIA)
  => true

Load the Listeria CSV file into a QTL object

  >> qtl = QTL.new(LISTERIA)

Alternatively provide the allowed genotypes for validation

  >> validate = QtlValidateGenotypes.new(['A','B'],['A','H','B','D','C'],['-','NA'])
  >> qtl = QTL.new(LISTERIA,validate)

For the heck of it we make sure it is there

  >> d.individuals.size
  => 120

Now we follow the MQM tutorial in FIXME: location

=end


$: << '..'
require 'qtl/rqtl'
require 'test/unit'

TESTDATADIR = '../../../test/data/qtl'
LISTERIAFN  = TESTDATADIR+'/listeria.csv'

# require 'test/unit/testcase'

class TestBiolibRQtlMQM < Test::Unit::TestCase

  def setup
    @qtl = QTL.new(LISTERIAFN)
  end

  def test_info
    d = @qtl.data
    assert_equal(:f2,d.type)
    assert_equal(120,d.individuals.size)
    assert_equal(133,d.totmar)
    assert_equal([["1", 13], ["10", 5], ["11", 6], ["12", 6], ["13", 12], ["14", 4], ["15", 8], ["16", 4], ["17", 4], ["18", 4], ["19", 4], ["2", 6], ["3", 6], ["4", 4], ["5", 13], ["6", 13], ["7", 6], ["8", 6], ["9", 7], ["X", 2]],d.nmar.sort)
  end

end

end # $UNITTEST
