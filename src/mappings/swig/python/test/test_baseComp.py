import sys
sys.path += ['../libsequence']

from biolib.libsequence import *



name = raw_input("Please enter the name of sequence:")
seq = raw_input("Please enter the sequence itself:")
x = Fasta(name,seq)

count = stateCounter()
for s in seq:
    count(s)

if count.ndna == False:
    leng = x.length() - count.gap - count.n

    perA = (float)(count.a) / leng;
    perG = (float)(count.g) / leng;
    perC = (float)(count.c) / leng;
    perT = (float)(count.t) / leng;

    print "using Sequence::stateCounter:"
    print "A",perA
    print "G",perG
    print "C",perC
    print "T",perT

else:
    print "non-DNA character encountered. Skipping.\n"


