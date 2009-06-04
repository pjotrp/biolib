
# gdb ruby
# directory /home/wrk/izip/git/opensource/biolib/src/mappings/swig/ruby/rqtl:/home/wrk/izip/git/opensource/biolib/src/clibs/rqtl/src/
# run -I../../rqtl/build debug.rb
#
$: << '..'
$: << '../../../mappings/swig/ruby/rqtl/'

require 'qtl/rqtl'

DIR = '../../../test/data/qtl'
LISTERIA  = DIR+'/listeria.csv'
validate = QtlValidateGenotypes.new(['A','B'],['A','H','B','D','C'],['-','NA'])
qtl = QTL.new(LISTERIA,validate)
rqtl = RQTL.new(qtl)
mr = rqtl.scanone_mr()
p ["mr",mr]
p mr[0].to_a
#    => ['D10M44','1',0.0,0.457256443]

