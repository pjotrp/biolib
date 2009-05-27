# Ruby DocTest
#
# Run with ./runner.rb or
#
#   ../../../../tools/rubydoctest/bin/rubydoctest test_rqtl.rb
#
# Documentation with rd2 -r rd/rd2html-lib *.rb

$: << '../../../mappings/swig/ruby/rqtl/'

=begin

Here we load the R/qtl Listeria dataset (from a CSV) and verify the
resulting information matches that of the R version (see RQTL book page 46).

Find the special classes for loading QTL input files (part of BioLib 'extra').

  >> $: << '..'
  >> require 'qtl/rqtl'

Locate the Listeria input file
 
  >> DIR = '../../../test/data/qtl'
  >> LISTERIA  = DIR+'/listeria.csv'
  >> File.exist?(LISTERIA)
  => true

Load the Listeria CSV file into a QTL object

  >> qtl = QTL.new(LISTERIA)

You can also provide the allowed genotypes:

  >> validate = QtlValidateGenotypes.new(['A','B'],['A','H','B','D','C'],['-','NA'])
  >> qtl = QTL.new(LISTERIA,validate)

Fetch the loaded data and check the type (defaults to F2 at this point)
R/qtl makes it an F2 intercross based on the number of genotypes

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

Number of phenotypes (T264. R/qtl adds sex and pgm automagically)

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

The names are sorted, so we can validate the contents

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

  >> d.markers['D10M44'].mid
  => 0

Markers carry an indexed 'mid'. This is really superfluous when genome 
information is available on marker positions. But it can be useful to speed
queries up:

Find marker by index ('mid')

  >> d.markers[0].name
  => 'D10M44'

or the equivalent

  >> d.marker(0).name
  => 'D10M44'

  >>  d.marker(0).position
  => 0

  >>  d.marker(1).position
  => 0.99675

  >>  d.marker(0).chromosome
  => '1'

  >>  d.marker(14).chromosome
  => '2'

  >> d.markers.size
  => 133

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

  def test_phenotyped
    d = @qtl.data
    assert_equal([96.7],d.perc_phenotyped)
  end

  def test_genotyped
    d = @qtl.data
    assert_equal(88.5,d.perc_genotyped)
  end

=begin

Get phenotype information for the listeria set (only one 
defined here.

  >> d.phenotype(0,0)
  => 118.317
 
  >> d.phenotype(1,0)
  => 264
 
=end

=begin
R/qtl's genotype matrix for the listeria set contains

      D1M291    D1M209    D1M155
    84.93474  92.68394  93.64344
           H         H         H
           H         H         H
           B         B         B
           B         B         B
           H         H         H
           B         B         B
           H         H         H
           H         H         H
           H         -         H

which translates internally to:

      D1M291    D1M209    D1M155
           2         2         2
           2         2         2
           3         3         3
           3         3         3
           2         2         2
           3         3         3
           2         2         2
           2         2         2
           2        NA         2

Raw names read from input file

  >> d.genotypes.namesread.sort
  => [["-", 1840], ["A", 3701], ["B", 3387], ["C", 128], ["H", 6904]]

Validated names

  >> d.genotypes.names.sort
  => ["A", "B", "C", "H"]

  >> d.genotypes.na.sort
  => ["-", "NA"]

  >> d.genotypes.alleles.sort
  => ["A", "B"]

First we get the original values from the Listeria .csv file
(individual/marker):

  >> d.individuals[1].genotypes[2].value
  => "B"

  >> d.markers['D1M291'].mid
  => 10

  >> d.individuals[1].genotypes[d.markers['D1M291'].mid].value
  => 'H'

The same, but nicer, query by individual/marker 

  >> d.genotype(0,0)
  => 'B'

  >> d.genotype(1,0)
  => '-'

  >> d.genotype(1,2)
  => 'B'

  >> d.genotype(1,'D1M291')
  => 'H'

  >> d.genotype(2,'D2M493')
  => '-'

  >> d.genotype(0,'D13M106')
  => 'A'

  >> d.genotype(2,'D13M106')
  => 'H'

Here we create an adapter for translating genotype information into an
input object suitable for use by R/qtl. Normally a user won't do this, 
as a qtl object is handled transparently.

  >> r = RQtlInputAdaptor.new(d)

  >> r.genotype(1,'D1M291')
  => 2

  >> r.genotype(8,'D1M209')
  => 'NA'

  >> r.genotype(3,'D1M155')
  => 3

  >> r.genotype(8,'D10M44')
  => 1

  >> d.genotypes.names
  => ["A", "B", "C", "H"]

  >> r.genotypes.names
  => [1,3,4,2]

  >> r.genotypes.alleles
  => [1,3]

  >> r.genotypes.na
  => ["NA","NA"]

=end

  def test_genotype_adaptor
    d = @qtl.data
    assert_equal('B',d.genotype(0,0))
    r = RQtlInputAdaptor.new(d)
    assert_equal(3,r.genotype(0,0))
    assert_equal(2,r.genotype(1,'D1M291'))
    assert_equal([1,3,4,2],r.genotypes.names)
  end


=begin

We are going to scan for QTL's. The first R equivalent here is:

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

Execute single QTL mapping using R/qtl's marker regression passing in
the @qtl dataset. We need the RQTL convenience class to map against biolib:

    >> require 'qtl/rqtl'
    >> rqtl = RQTL.new(qtl)

Now execute QTL mapping with scanone

    >> mr = rqtl.scanone_mr()
    >> p ["mr",mr]

Which returns and array of markers containing the marker name, chromosome,
position and lod score:

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
    mr = rqtl.scanone_mr()
    return
    assert_equal('D1M215',mr[3].name) 
    assert_equal('1',mr[3].chr) 
    assert_equal(40.41361,mr[3].pos) 
    assert_equal(0.070120158,mr[3].lod) 
    assert_equal(['D10M44','1',0.0,0.457256443],mr[0].to_a)
  end
end

if $0 == __FILE__

  require 'qtl/rqtl'

  fn = LISTERIAFN

  raise 'File not found error' if !File.exist?(fn)

  qtl = QTL.new(fn)
  # These are some simple tests to see if the build system worked...
  d = qtl.data
  # raise 'Read test failed' if qtl.data.phenotypenames[0] != 118.317
  raise 'Read test failed' if qtl.data.marker(0).name != 'D10M44'
  raise 'Read test failed' if qtl.data.marker(13).chromosome != '2'

  print "Success!"
end
