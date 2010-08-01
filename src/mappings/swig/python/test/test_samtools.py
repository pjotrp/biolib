
import sys

sys.path += ['../samtools']
print sys.path

import biolib.samtools as samtools

datadir = '../../../../test/data/trace'
samgz = datadir+'/ex1.sam.gz'

result = samtools.samopen(samgz,'r',None)
sys.exit(0)
