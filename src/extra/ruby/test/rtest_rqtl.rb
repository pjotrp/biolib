# Ruby Regression Test for R/qtl support
#

cwd = File.dirname(__FILE__)
Dir.chdir(cwd)

$: << '../../../mappings/swig/ruby/rqtl/'
$: << '../../../mappings/swig/ruby/biolib_core/'
$: << '../../../mappings/swig/ruby/biolib_R/'

require 'biolib/biolib_core'

Biolib::Biolib_core.biolib_setloglevel(7)

$: << '..'
require 'qtl/rqtl'

TESTDATADIR = '../../../test/data/qtl'
RTESTDIR = '../../../test/regression/qtl'
LISTERIAFN  = TESTDATADIR+'/listeria.csv'

qtl = QTL.new(LISTERIAFN)

require 'qtl/rqtl'

fn = LISTERIAFN

raise 'File not found error' if !File.exist?(fn)

require 'qtl/rqtl'
rqtl = RQTL.new(qtl)
# These are some simple tests to see if the build system worked...
d = qtl.data
# raise 'Read test failed' if qtl.data.phenotypenames[0] != 118.317
raise 'Read test failed' if qtl.data.marker(0).name != 'D10M44'
raise 'Read test failed' if qtl.data.marker(13).chromosome != '2'

File.open(RTESTDIR+'/scanone_mr.rnew','w') do | f |
  mr = rqtl.scanone_mr()
  mr.each do | m |
    f.print m.pretty
  end
end
