import sys
sys.path += ['../libsequence']
#print sys.path
#import biolib.libsequence as libsequence
from biolib.libsequence import *


##############class Fasta##############################
#########input########
##infas = Fasta()
##print "Please input sequence in FASTA format:\n"
##infas.read(cin)
##print infas.GetName()
##print infas.GetSeq()
##print
#########output#########
##print "next print a sequence in FASTA format:\n"
##outfas = Fasta('seq2', 'ATGTTGGTTAG')
##outfas._print(cout)
##print 
##
########################################################

###############class newick_stream_marginal_tree############
##########output#########
##outmarg = init_marginal(10)
##n = newick_stream_marginal_tree(outmarg)
##print "print a marginal tree in Newick format:\n"
##n._print(cout)
##print
#############################################################




###########################class SimData##########################
###########input#############
##ind = SimData()
##ind.read(cin)
##print ind.GetData()
##print ind.GetPositions()
##print

##########output#######
##pos = doubleVector(4)
##pos[0] = .25
##pos[1] = .32
##pos[2] = .34
##pos[3] = .44
##dat = strVector(2)
##dat[0] = 'A-TC'
##dat[1] = 'N0G1'
##outd = SimData(pos,dat)
##outd._print(cout)
##print
##

####################################################################

v = fastaVector(2)
v[0] = Fasta('s1','ATGCG')
v[1] = Fasta('s2','CG-TT')
inp = PolySites(v)
inp._print(cout)
print

outp = PolySites()
outp.read(cin)



