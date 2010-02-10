use biolib::staden_io_lib;

$datadir = '../../../../test/data/trace';

# Read test data - reading one record from file
$procsrffn = "$datadir/abi3700-ztr/1dJ671C13-2a01.q1c.ztr";
print "Parsing trace file ",$procsrffn;

print "\nTT_ZTR=",$staden_io_lib::TT_ZTR;

$result = staden_io_lib::read_reading($procsrffn,$staden_io_lib::TT_ANY);

print("\nformat=",staden_io_libc::Read_format_get($result));
print("\nNBases=",$result->{NBases});
print("\nbase=",staden_io_libc::Read_base_get($result));

croak('Read test failed') if $result->{NBases} != 766;

# Now write record to test SCF file
$wresult = staden_io_lib::write_reading('test.scf', $result, 0);
croak('Write test failed') if $wresult != 0 or ! -e 'test.scf';
unlink('test.scf');

# Let's try a multi-read using a stateful file pointer, like the example in
# staden's ./progs/extract_fastq.c. It repeats 
#
#   Read *r = mfread_reading(mFILE *infp, char *in_file, int format)
#
# over a trace file, opened as 
#
#   mFile *infp = open_exp_mfile(char *fn, char *path);
#
# or
#
#   mFile *infp = open_trace_mfile(char *fn, char *path);
#
# In fact, read_read also uses mfread_read, but only once (see Read.c).
#
# In Perl:

$infp = staden_io_lib::open_exp_mfile($procsrffn,"");
$result = staden_io_lib::mfread_reading($infp,$procsrffn,$staden_io_lib::TT_ANY);
print("\nNBases=",$result->{NBases});
print("\nbase=",staden_io_libc::Read_base_get($result));

# and another time
$result = staden_io_lib::mfread_reading($infp,$procsrffn,$staden_io_lib::TT_ANY);
print("\nNBases=",$result->{NBases});
print("\nbase=",staden_io_libc::Read_base_get($result));

# So it retains the $infp. However, it does not recognise the EOF

# close the file
staden_io_lib::mfclose($infp);

exit 0;
