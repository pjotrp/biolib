use biolib::samtools;

$datadir = '../../../../test/data/samtools';

$samfn = "$datadir/ex3.sam";

$fh = samtools::samopen($samfn,"r",undef);
$count = 0;
$bytesread = 0;
while ($bytesread >= 0) {
  $count += 1;
  $bam = samtools::bam_init1();
  $bytesread = samtools::samread($fh,$bam);
  $data = samtools::bam1_t_datalist_get($bam);

  print "\n> rec,bytesread=", $count, ", ", $bytesread;
  print "\n> bam.core.tid=",$bam->{core}->{tid}," (chromosome nr)";
  print "\n> bam.core.pos=",$bam->{core}->{pos}," (chromosome pos)";
  # print "\n> bam1_qname($bam)=",data
  print "\n> bam.data_len=",$bam->{data_len};
  print "\n> bam.m_data=",$bam->{m_data};
  # print "\n>",bam.data_len
  print "\n<",$data,">\n";
  # cleanup bam record
  samtools::bam_destroy1($bam);
}
samtools::samclose($fh);
exit 0;
