# Convert SAM to BAM with Perl
#

use biolib::samtools;

$datadir = '../../../../test/data/samtools';

$fafn  = "$datadir/ex1.fa";
$samfn = "$datadir/ex1.sam.gz";
$faifn = "$datadir/ex1.fa.fai";
$bamfn = "/tmp/ex1.bam.gz";

$fh1 = samtools::samopen($samfn,"r",undef);
if ($f1==undef or $f1->{header}->{n_targets} == 0) {
  print "Using fai\n";
	samtools::fai_build($fafn);
  $fh1 = samtools::samopen_listfn($samfn,"r",$faifn);
}
$bamheader = $fh1->{header};
print("targets=",$bamheader->{n_targets},"\n");
$fh2 = samtools::samopen($bamfn,"wb",$bamheader);

$bytesread = 0;
while ($bytesread >= 0) {
  $bambuf = samtools::bam_init1();
  $bytesread = samtools::samread($fh1,$bambuf);
	last if $bytesread < 0;
	print ".";
	$byteswritten = samtools::samwrite($fh2,$bambuf);
  samtools::bam_destroy1($bambuf);
}
samtools::samclose($fh1);
samtools::samclose($fh2);
