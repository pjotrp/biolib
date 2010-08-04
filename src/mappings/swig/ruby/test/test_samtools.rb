
# print "PATH=",ENV['PATH'],"\n"
# p $:

require 'biolib/samtools'

datadir = '../../../../test/data/samtools'
fn = datadir+'/ex3.sam'
raise 'Error can not find '+fn if !File.exist?(fn)

fh = Biolib::Samtools.samopen(fn,"r",nil)
bam = Biolib::Samtools.new_bam()
num = Biolib::Samtools.samread(fh,bam)
print "\n>>> num=",num
print "\n>>> bam.data_len=",bam.data_len
print "\n>>> bam.m_data=",bam.m_data
print "\n>>>",bam.data_len,':',bam.data,"\n"
data = Biolib::Samtools.bam1_t_datalist_get(bam)
num = Biolib::Samtools.samread(fh,bam)
print "\n>>> num=",num
print "\n>>> bam.data_len=",bam.data_len
print "\n>>> bam.m_data=",bam.m_data
print "\n>>>",bam.data,"\n"
data = Biolib::Samtools.bam1_t_datalist_get(bam)
p [data[0],data[1],data]
num = Biolib::Samtools.samread(fh,bam)
print "\n>>> num=",num
print "\n>>> bam.data_len=",bam.data_len
print "\n>>> bam.m_data=",bam.m_data
print "\n>>>",bam.data,"\n"
data = Biolib::Samtools.bam1_t_datalist_get(bam)
p [data[0],data[1],data]
num = Biolib::Samtools.samread(fh,bam)
print "\n>>> num=",num
print "\n>>> bam.data_len=",bam.data_len
print "\n>>> bam.m_data=",bam.m_data
print "\n>>>",bam.data,"\n"
data = Biolib::Samtools.bam1_t_datalist_get(bam)
p [data[0],data[1],data]
num = Biolib::Samtools.samread(fh,bam)
print "\n>>> num=",num
Biolib::Samtools.samclose(fh)

exit 0
