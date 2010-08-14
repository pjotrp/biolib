#
# Run with "/usr/bin/ruby" "-I.." "./../test/test_sam2bam.rb"

require 'biolib/samtools'
require 'tempfile'

datadir = '../../../../test/data/samtools'

#--- convert SAM+FASTA to BAM file
datadir = '.'
fafn  = datadir+'/ex1.fa'
samfn = datadir+'/ex1.sam.gz'
faifn = datadir+'/ex1.fa.fai'
bamfn = '/tmp/ex1.bam.gz'
fafn  = nil
samfn = datadir+'/ex3.sam'
faifn = nil
bamfn = '/tmp/ex3.bam.gz'
#--- first create the faifn from the FASTA file
print "Write #{faifn}\n"
# if Biolib::Samtools.fai_build(fafn) >= 0
#  bamheader = Biolib::Samtools.sam_header_read2(faifn)
  # print "targets=",bamheader.n_targets,"\n"
  print "Read #{samfn}\n"
  # fh1 = Biolib::Samtools.samopen(samfn,"r",bamheader) # use header when no SQ lines
  fh1 = Biolib::Samtools.samopen(samfn,"r",nil) # use header when no SQ lines
  # header = Biolib::Samtools.sam_header_read(fh1)
  fh2 = Biolib::Samtools.samopen_listfn(bamfn,"bw",faifn)  
  bytesread=0
  print "\n::: "
  while bytesread >= 0
    print "r"
    bambuf = Biolib::Samtools.bam_init1()
    bytesread = Biolib::Samtools.samread(fh1,bambuf)
    print bytesread,"\n"
    break if bytesread < 0
    print "w"
    bytesread = Biolib::Samtools.samwrite(fh2,bambuf)
    Biolib::Samtools.bam_destroy1(bambuf)
  end
  Biolib::Samtools.samclose(fh1)
  Biolib::Samtools.samclose(fh2)
# end
exit 0
