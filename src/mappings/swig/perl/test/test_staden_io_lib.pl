use biolib::staden_io_lib;

$datadir = '../../../../test/data/trace';

# Read test data
$procsrffn = "$datadir/abi3700-ztr/1dJ671C13-2a01.q1c.ztr";
print "Parsing trace file ",$procsrffn;

print "\nTT_ZTR=",$staden_io_lib::TT_ZTR;
$result = staden_io_lib::read_reading($procsrffn,$staden_io_lib::TT_ANY);

print("\nformat=",staden_io_libc::Read_format_get($result));
print("\nNBases=",$result->{NBases});
print("\nbase=",staden_io_libc::Read_base_get($result));

croak('Read test failed') if $result->{NBases} != 766;

# Now write test SCF file
$wresult = staden_io_lib::write_reading('test.scf', $result, 0);
croak('Write test failed') if $wresult != 0 or ! -e 'test.scf';
unlink('test.scf');

exit 0;
