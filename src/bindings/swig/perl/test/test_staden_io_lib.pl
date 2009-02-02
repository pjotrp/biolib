use biolib::staden_io_lib;

$datadir = '../../../../test/data/trace';

$procsrffn = "$datadir/abi3700-ztr/1dJ671C13-2a01.q1c.ztr";
print "Parsing trace file ",$procsrffn;

print "\nTT_ZTR=",$staden_io_lib::TT_ZTR;
$result = staden_io_lib::read_reading($procsrffn,$staden_io_lib::TT_ANY);

print("\nformat=",staden_io_libc::Read_format_get($result));
print("\nNBases=",staden_io_libc::Read_NBases_get($result));
print("\nbase=",staden_io_libc::Read_base_get($result));

croak('Test failed') if staden_io_libc::Read_NBases_get($result) != 766;

exit 0;
