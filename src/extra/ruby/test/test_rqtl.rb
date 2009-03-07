# Ruby DocTest

=begin

Here we load the R/QTL Listeria dataset (from a CSV) and verify the
resulting information matches that of the R version (see RQTL book page 46).

Find the special classes for loading QTL input files (part of BioLib 'extra').

  >> $: << '..'
  >> require 'qtl/qtl'

Locate the Listeria input file
 
  >> TESTDATADIR = '../../../test/data/qtl'
  >> LISTERIA  = TESTDATADIR+'/listeria.csv'
  >> File.exist?(LISTERIA)
  => true

Load the Listeria CSV file into a QTL object

  >> qtl = QTL.new(LISTERIA)

Fetch the loaded data and check the type (defaults to F2 at this point)
R/QTL makes it an F2 intercross based on the number of genotypes

  >> d = qtl.data
  >> d.type
  => 'F2'

Return the number of individuals

  >> d.individuals.size
  => 120

The short notation - get number of individuals

  >> d.nind
  => 120

Number of phenotypes (T264. R/QTL adds sex and pgm automagically)

  >> d.nphe
  => 1

Number of markers

  >> d.totmar
  => 133

Number of chromosomes

  >> d.nchr
  => 20

Markers per chromosome

  >> d.nmar.sort
  => [["1", 13], ["10", 5], ["11", 6], ["12", 6], ["13", 12], ["14", 4], ["15", 8], ["16", 4], ["17", 4], ["18", 4], ["19", 4], ["2", 6], ["3", 6], ["4", 4], ["5", 13], ["6", 13], ["7", 6], ["8", 6], ["9", 7], ["X", 2]]

  >> d.marker(0).name
  => 'D10M44'

  >>  d.marker(14).chromosome
  => '2'

  >> d.markers.size
  => 133

NYI the following:

  !>> d.chromosomes.x.name
  !=> 'X'
  !>> d.chromosomes[1].markers.size
  !=> 13

=end


$: << '..'
require 'qtl/qtl'
require 'test/unit'

TESTDATADIR = '../../../test/data/qtl'
LISTERIAFN  = TESTDATADIR+'/listeria.csv'

# require 'test/unit/testcase'

class TestBiolibRQtl < Test::Unit::TestCase

  def setup
    @qtl = QTL.new(LISTERIAFN)
  end

  def test_info
    d = @qtl.data
    assert_equal('F2',d.type)
    assert_equal(120,d.individuals.size)
    assert_equal(120,d.nind)
    assert_equal(1,d.nphe)
    assert_equal(133,d.totmar)
    assert_equal(20,d.nchr)
    assert_equal([["1", 13], ["10", 5], ["11", 6], ["12", 6], ["13", 12], ["14", 4], ["15", 8], ["16", 4], ["17", 4], ["18", 4], ["19", 4], ["2", 6], ["3", 6], ["4", 4], ["5", 13], ["6", 13], ["7", 6], ["8", 6], ["9", 7], ["X", 2]],d.nmar.sort)
  end

  def test_markers
    d = @qtl.data
    assert_equal('D10M44',d.marker(0).name)
    assert_equal('2',d.marker(14).chromosome)
    assert_equal(133,d.markers.size)
  end

=begin

Chromosome info

  >> d.chromosomes.size
  => 20
  >> d.chromosomes.autosomes.size
  => 19

=end

  def test_chromosomes
    d = @qtl.data
    assert_equal(20,d.chromosomes.size)
    assert_equal(19,d.chromosomes.autosomes.size)
    # assert_equal('X',d.chromosomes.x.name)
    # assert_equal(13,d.chromosomes[1].markers.size)
  end

=begin

Phenotype column info

  >> d.phenotypecolumn(0).name
  => 'T264'
  >> d.phenotypecolumns.size
  => 1

=end

  def test_phenotypecolumns
    d = @qtl.data
    assert_equal('T264',d.phenotypecolumn(0).name)
    assert_equal(1,d.phenotypecolumns.size)
  end

=begin

Get statistics

  >> d.perc_phenotyped
  => [96.7]
  >> d.perc_genotyped
  => 88.5

=end

  def test_phenotype
    d = @qtl.data
    assert_equal([96.7],d.perc_phenotyped)
  end

  def test_genotype
    d = @qtl.data
    assert_equal(88.5,d.perc_genotyped)
  end

end

if $0 == __FILE__

  fn = LISTERIAFN

  raise 'File not found error' if !File.exist?(fn)

  qtl = QTL.new(fn)
  # These are some simple tests to see if the build system worked...
  # raise 'Read test failed' if qtl.data.phenotype(0) != 118.317
  # raise 'Read test failed' if qtl.data.marker(0).name != 'D10M44'
  # raise 'Read test failed' if qtl.data.marker(13).chromosome != 2

  print "Success!"
end
