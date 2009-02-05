# Merely tests opening a file. For a full library test see the Ruby
# test case.

use biolib::affyio;


$DATA_REPOSITORY = 'http://bio3.biobeat.org/download/biolib/data/';

$datadir = '../../../../test/data/microarray/affy';
$cdffilename = '/tmp/test_cdf.dat';
# celfilename = datadir + '/test46.CEL.gz';
#   celfilename = datadir + '/test_binary.cel.gz';

print "Loading $cdffilename...\n";
if (! -e $cdffilename) {
  print `wget -O $cdffilename.gz $DATA_REPOSITORY/test_cdf.dat.gz` ;
  print `gzip -d $cdffilename.gz`
}
$cdf = affyio::open_cdffile($cdffilename);
$probesets = affyio::cdf_num_probesets($cdf);

print "CDFinfo probesets=",$probesets;

exit ($probesets==22293); 
