
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
print "\n>>>",bam.data,"\n"
p bambam.data
num = Biolib::Samtools.samread(fh,bam)
print "\n>>> num=",num
print "\n>>> bam.data_len=",bam.data_len
print "\n>>> bam.m_data=",bam.m_data
print "\n>>>",bam.data,"\n"
num = Biolib::Samtools.samread(fh,bam)
print "\n>>> num=",num
print "\n>>> bam.data_len=",bam.data_len
print "\n>>> bam.m_data=",bam.m_data
print "\n>>>",bam.data,"\n"
num = Biolib::Samtools.samread(fh,bam)
print "\n>>> num=",num
print "\n>>> bam.data_len=",bam.data_len
print "\n>>> bam.m_data=",bam.m_data
print "\n>>>",bam.data,"\n"
num = Biolib::Samtools.samread(fh,bam)
print "\n>>> num=",num
Biolib::Samtools.samclose(fh)

exit 0
