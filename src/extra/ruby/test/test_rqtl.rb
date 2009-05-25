# Ruby DocTest
#
# Run with ./runner.rb or
#
#   ../../../../tools/rubydoctest/bin/rubydoctest test_rqtl.rb
#
# Documentation with rd2 -r rd/rd2html-lib *.rb


$: << '../../../mappings/swig/ruby/rqtl/'

=begin

Here we load the R/QTL Listeria dataset (from a CSV) and verify the
resulting information matches that of the R version (see RQTL book page 46).

Find the special classes for loading QTL input files (part of BioLib 'extra').

  >> $: << '..'
  >> require 'qtl/qtl'

Locate the Listeria input file
 
  >> DIR = '../../../test/data/qtl'
  >> LISTERIA  = DIR+'/listeria.csv'
  >> File.exist?(LISTERIA)
  => true

Load the Listeria CSV file into a QTL object

  >> qtl = QTL.new(LISTERIA)

Fetch the loaded data and check the type (defaults to F2 at this point)
R/QTL makes it an F2 intercross based on the number of genotypes


  >> d = qtl.data
  >> d.type
  => 'F2'

Here we get information from the data object. There are two 'styles'. One is
standard Ruby's principles of least surprise. The other is the one used by
R/qtl.

Return the number of individuals

  >> d.individuals.size
  => 120

The short R/qtl notation - get number of individuals

  >> d.nind
  => 120

Number of phenotypes (T264. R/QTL adds sex and pgm automagically)

  >> d.phenotypenames.size
  => 1

  >> d.nphe
  => 1

Number of markers

  >> d.markers.size
  => 133

  >> d.totmar
  => 133

Number of chromosomes

  >> d.chromosomes.size
  => 20

  >> d.chromosomes.names.sort
  => ["1", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "2", "3", "4", "5", "6", "7", "8", "9", "X"]

  >> d.nchr
  => 20


Markers per chromosome

  >> d.nmar.sort
  => [["1", 13], ["10", 5], ["11", 6], ["12", 6], ["13", 12], ["14", 4], ["15", 8], ["16", 4], ["17", 4], ["18", 4], ["19", 4], ["2", 6], ["3", 6], ["4", 4], ["5", 13], ["6", 13], ["7", 6], ["8", 6], ["9", 7], ["X", 2]]

Find marker by name

  >> d.markers['D10M44'].name
  => 'D10M44'

Find marker by index

  >> d.markers[0].name
  => 'D10M44'

Markers carry an indexed 'mid'. This is really superfluous when genome 
information is available on marker positions.

  >> d.markers['D10M44'].mid
  => 0

  >> d.marker(0).name
  => 'D10M44'

  >>  d.marker(14).chromosome
  => '2'

  >> d.markers.size
  => 133

R/qtl's genotype matrix for the listeria set looks like this:

     D1M291 D1M209 D1M155
[1,]      2      2      2
[2,]      2      2      2
[3,]      3      3      3
[4,]      3      3      3
[5,]      2      2      2
[6,]      3      3      3
[7,]      2      2      2
[8,]      2      2      2
[9,]      2     NA      2

  >> d.genotypes.size
  => 4

First we get the original values from the Listeria .csv file:

  >> d.genotype(1,'D1M291')
  => 2

  >> d.genotype(9,'D1M209')
  => NA

Now we are going to create an adapter for translating dataset into an
input object suitable for use by R/qtl.

  >> r = RQtlInputAdaptor(d)

  >> r.genotype(1,'D1M291')
  => 2

  >> r.genotype(9,'D1M209')
  => NA

  >> r.genotype(3,'D1M155')
  => 3

  >> r.genotype(9,'D10M44')
  => 1

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

  >> d.phenotypenames[0].name
  => 'T264'
  >> d.phenotypenames.size
  => 1

=end

  def test_phenotypecolumns
    d = @qtl.data
    assert_equal('T264',d.phenotypenames[0].name)
    assert_equal(1,d.phenotypenames.size)
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

=begin

The R equivalent is:

    > mr = scanone(data,method='mr')
      Warning message:
      Dropping 4 individuals with missing phenotypes.
        in: checkcovar(cross, pheno.col, addcovar, intcovar, perm.strata,  

    > mr
              chr      pos         lod
      D10M44    1  0.00000 0.457256443
      D1M3      1  0.99675 0.687377692
      D1M75     1 24.84773 0.244500303
      D1M215    1 40.41361 0.070120158
      (...)
      D19M117  19 16.36398 0.436675089
      D19M65   19 32.82935 0.007363598
      D19M10   19 44.49432 0.000000000
      DXM186    X  0.00000 0.678435461
      DXM64     X 42.34593 0.002756074

Execute single QTL mapping using R/QTL's marker regression passing in
the @qtl dataset. We need the RQTL convenience class to map against biolib:

    >> require 'qtl/rqtl'
    >> rqtl = RQTL.new(@qtl)

Now execute QTL mapping with scanone

    >> mr = rqtl.scanone(:method => 'mr')

Return the marker name, chromosome, position and lod score:

    >> mr[0].to_a
    => ['D10M44','1',0.0,0.457256443]

or per attribute:

    >> mr[3].name
    => 'D1M215'
    >> mr[3].chromosome
    => '1'
    >> mr[3].pos
    => 40.41361 
    >> mr[3].lod
    => 0.070120158

=end

  def test_scanone
    rqtl = RQTL.new(@qtl)
    mr = rqtl.scanone(:method => 'mr')
    return
    assert_equal('D1M215',mr[3].name) 
    assert_equal('1',mr[3].chr) 
    assert_equal(40.41361,mr[3].pos) 
    assert_equal(0.070120158,mr[3].lod) 
    assert_equal(['D10M44','1',0.0,0.457256443],mr[0].to_a)
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
