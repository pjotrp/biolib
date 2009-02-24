
$: << '../../../../biolib/ruby'
# require 'biolib/rqtl'
require 'qtl/qtl'

TESTDATADIR = '../../../../test/data/qtl'
LISTERIAFN  = TESTDATADIR+'/listeria.csv'

require 'test/unit/testcase'

class Test_Biolib_RQtl < Test::Unit::TestCase

  def setup
    @qtl = QTL.new(LISTERIAFN)
  end

  def test_info
    assert_equal('F2 intercross',d.type)
    assert_equal(120,d.individuals.size)
  end

  def test_markers
    d = @qtl.data
    assert_equal('D10M44',d.marker(0).name)
    assert_equal('2',d.marker(14).chromosome)
    assert_equal(133,d.markers.size)
  end

  def test_chromosomes
    d = @qtl.data
    assert_equal(20,d.chromosomes.size)
    assert_equal(19,d.chromosomes.autosomes.size)
    assert_equal('X',d.chromosomes.x.name)
  end

  def test_phenotypecolumns
    d = @qtl.data
    assert_equal('T264',d.phenotypecolumn(0).name)
    assert_equal(2,d.phenotypecolumns.size)
  end

  def test_phenotype
    d = @qtl.data
    assert_equal([96.7, 100],d.perc_phenotyped)
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
  raise 'Read test failed' if qtl.data.phenotype(0) != 118.317
  raise 'Read test failed' if qtl.data.marker(0).name != 'D10M44'
  raise 'Read test failed' if qtl.data.marker(13).chromosome != 2

  print "Success!"
  exit 0
end
