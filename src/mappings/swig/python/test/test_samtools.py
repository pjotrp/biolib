
import sys

sys.path += ['../samtools']
print sys.path

import biolib.samtools as samtools

datadir = '../../../../test/data/samtools'
samfn = datadir+'/ex3.sam'

fh = samtools.samopen(samfn,'r',None)
count = 0
bytesread = 0
while (bytesread >= 0):
  count = count + 1
  print("#",count)
  bam = samtools.new_bam()
  bytesread = samtools.samread(fh,bam)
  if bytesread < 0:
    print("done")
    break
  data = samtools.bam1_t_datalist_get(bam)
  print("> bytesread=", bytesread)
  print "> bam.core.tid=",bam.core.tid," (chromosome nr)"
  print "> bam.core.pos=",bam.core.pos," (chromosome pos)"
  print "> bam.data_len=",bam.data_len
  print "> bam.m_data=",bam.m_data
  print ">",bam.data_len
  print data
  print("")
  # cleanup bam record
  samtools.free_bam(bam)

samtools.samclose(fh)
sys.exit(0)
