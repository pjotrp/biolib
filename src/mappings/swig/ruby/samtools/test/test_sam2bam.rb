#
# Run with "/usr/bin/ruby" "-I.." "./../test/test_sam2bam.rb"

require 'biolib/samtools'
require 'tempfile'

datadir = '../../../../test/data/samtools'

#--- convert SAM+FASTA to BAM file
fafn  = datadir+'/ex1.fa'
samfn = datadir+'/ex1.sam.gz'
faifn = datadir+'/ex1.fa.fai'
bamfn = '/tmp/ex1.bam.gz'
# samfn = datadir+'/ex3.sam'
# bamfn = '/tmp/ex3.bam.gz'
raise "#{samfn} does not exist" if !File.exist?(samfn)
fh1 = Biolib::Samtools.samopen(samfn,"r",nil) # use header when no SQ lines
if fh1 == nil or fh1.header.n_targets == 0
  print "No header information in #{samfn}, creating fai!\n"
  raise "#{fafn} does not exist" if !File.exist?(fafn)
  raise "Can not create faifn from #{fafn}" if Biolib::Samtools.fai_build(fafn) < 0 
  fh1 = Biolib::Samtools.samopen_listfn(samfn,"r",faifn)
end
bamheader = fh1.header
print "targets=",bamheader.n_targets,"\n"
fh2 = Biolib::Samtools.samopen(bamfn,"wb",bamheader)  
bytesread=0
while bytesread >= 0
  bambuf = Biolib::Samtools.bam_init1()
  bytesread = Biolib::Samtools.samread(fh1,bambuf)
  print bytesread,"\n"
  break if bytesread < 0
  byteswritten = Biolib::Samtools.samwrite(fh2,bambuf)
  Biolib::Samtools.bam_destroy1(bambuf)
end
Biolib::Samtools.samclose(fh1)
Biolib::Samtools.samclose(fh2)
