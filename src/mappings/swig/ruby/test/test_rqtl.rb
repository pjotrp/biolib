
$: << '../../../../biolib/ruby'
# require 'biolib/rqtl'
require 'qtl/qtl'

datadir = '../../../../test/data/qtl'
fn      = datadir+'/listeria.csv'
 
raise 'File not found error' if !File.exist?(fn)

qtl = QTL.new(fn)
# These are some simple tests to see if the build system worked...
raise 'Read test failed' if qtl.data.phenotype(0) != 118.317
raise 'Read test failed' if qtl.data.marker(0).name != 'D10M44'
raise 'Read test failed' if qtl.data.marker(13).chromosome != 2

print "Success!"
exit 0
