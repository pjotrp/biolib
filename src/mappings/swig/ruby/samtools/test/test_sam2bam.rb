#
# Run with "/usr/bin/ruby" "-I.." "./../test/test_sam2bam.rb"

require 'biolib/samtools'
require 'tempfile'

datadir = '../../../../test/data/samtools'

#--- convert SAM+FASTA to BAM file
fafn  = datadir+'/ex1.fa'
samfn = datadir+'/ex1.sam.gz'
faifn = '/tmp/ex1.fa.fai'
bamfn = '/tmp/ex1.bam.gz'
#--- first create the faifn from the FASTA file
print "Write #{faifn}\n"
if Biolib::Samtools.fai_build(fafn) >= 0
  print "Read #{samfn}\n"
  fh1 = Biolib::Samtools.samopen(samfn,"r",nil)
  bamheader = Biolib::Samtools.sam_header_read2(faifn)
  fh2 = Biolib::Samtools.samopen(bamfn,"bw",bamheader)
  bytesread=0
  print ": "
  while bytesread >= 0
    print "r"
    bam = Biolib::Samtools.bam_init1()
    bytesread = Biolib::Samtools.samread(fh1,bam)
    break if bytesread < 0
    print "w"
    bytesread = Biolib::Samtools.samwrite(fh2,bam)
    Biolib::Samtools.bam_destroy1(bam)
  end
  Biolib::Samtools.samclose(fh1)
  # Biolib::Samtools.samclose(fh2)
else
  print "Error creating index\n"
end
exit 0
