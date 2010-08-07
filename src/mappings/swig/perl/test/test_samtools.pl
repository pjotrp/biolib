use biolib::samtools;

$datadir = '../../../../test/data/samtools';

$samfn = "$datadir/ex3.sam";

$result = samtools::samopen($samfn,"r",undef);

exit 0;
