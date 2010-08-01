use biolib::samtools;

$datadir = '../../../../test/data/trace';

$samgz = "$datadir/ex1.sam.gz";

$result = samtools::samopen($samgz,"r",undef);

exit 0;
