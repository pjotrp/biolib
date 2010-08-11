
# print "PATH=",ENV['PATH'],"\n"
# p $:

require 'biolib/samtools'
require 'tempfile'

datadir = '../../../../test/data/samtools'
fn = datadir+'/ex3.sam'
raise 'Error can not find '+fn if !File.exist?(fn)

savebam1 = Biolib::Samtools.bam_init1()

fh = Biolib::Samtools.samopen(fn,"r",nil)
count = 0
begin
  count += 1
  bam = Biolib::Samtools.bam_init1()
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
  Biolib::Samtools.bam_copy1(savebam1,bam) if count == 2
  # cleanup bam record
  Biolib::Samtools.bam_destroy1(bam)
end while true
Biolib::Samtools.samclose(fh)
# Write single record to BAM file
tempname=Tempfile.new('biolib_bamout')
fn = tempname.path
print "Writing #{fn}\n"
fh2 = Biolib::Samtools.samopen(fn,"bw",nil)
byteswritten = Biolib::Samtools.samwrite(fh,savebam1)
p byteswritten
Biolib::Samtools.samclose(fh2)
print "Done writing #{fn}\n"
Biolib::Samtools.bam_destroy1(savebam1)

exit 0
