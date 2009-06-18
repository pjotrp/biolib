# gdb /usr/bin/ruby
# directory /home/wrk/izip/git/opensource/biolib/src/mappings/swig/ruby/rqtl:/home/wrk/izip/git/opensource/biolib/src/clibs/rqtl/src/
# run -I../../rqtl/build debug.rb
#
$: << '..'
$: << '../../../mappings/swig/ruby/rqtl/'
$: << '../../../mappings/swig/ruby/biolib_R/'
$: << '../../../mappings/swig/ruby/biolib_core/'

require 'qtl/rqtl'

Biolib::Biolib_core.biolib_setloglevel(7)

DIR = '../../../test/data/qtl'
LISTERIA  = DIR+'/listeria.csv'
validate = QtlValidateGenotypes.new(['A','B'],['A','H','B','D','C'],['-','NA'])
qtl = QTL.new(LISTERIA,validate)
rqtl = RQTL.new(qtl)
# mr = rqtl.scanone_mr()
# p mr[0].to_a

mr = rqtl.scanone_imp(rqtl.sim_geno(2.5, 8))
p mr[74].to_a
print 'expected ["c2.loc52.5", "2", 52.2, 0.9199136]'
p mr[555].to_a


