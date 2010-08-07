
# print "PATH=",ENV['PATH'],"\n"
# p $:

require 'biolib/samtools'

datadir = '../../../../test/data/samtools'
fn = datadir+'/ex3.sam'
raise 'Error can not find '+fn if !File.exist?(fn)

fh = Biolib::Samtools.samopen(fn,"r",nil)
count = 0
begin
  count += 1
  bam = Biolib::Samtools.new_bam()
  bytesread = Biolib::Samtools.samread(fh,bam)
  break if bytesread < 0
  data = Biolib::Samtools.bam1_t_datalist_get(bam)
  print "\n> rec,bytesread=",count,', ',bytesread
  print "\n> bam.core.tid=",bam.core.tid," (chromosome nr)"
  print "\n> bam.core.pos=",bam.core.pos," (chromosome pos)"
  # print "\n> bam1_qname(bam)=",data
  print "\n> bam.data_len=",bam.data_len
  print "\n> bam.m_data=",bam.m_data
  print "\n>",bam.data_len
  p [data]
end while true
Biolib::Samtools.samclose(fh)

exit 0
