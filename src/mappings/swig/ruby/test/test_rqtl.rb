
$: << '../../../../biolib/ruby'
# require 'biolib/rqtl'
require 'qtl/qtl'

datadir = '../../../../test/data/qtl'
fn      = datadir+'/listeria.csv'
 
raise 'File not found error' if !File.exist?(fn)

qtl = QTL.new(fn)

print "Success!"
exit 0
