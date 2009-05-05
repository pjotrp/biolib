
print "PATH=",ENV['PATH'],"\n"
p $:

require 'biolib/staden_io_lib'

# $top_builddir/progs/srf2fasta $outdir/proc.srf > $outdir/slx.fasta 


datadir = '../../../../test/data/trace'
procsrffn = datadir+'/abi3700-ztr/1dJ671C13-2a01.q1c.ztr'
raise 'Error can not find '+procsrffn if !File.exist?(procsrffn)
p Biolib::Staden_io_lib::TT_ANY;

result = Biolib::Staden_io_lib.read_reading(procsrffn,Biolib::Staden_io_lib::TT_ANY)
p result.format
p result.NBases
p result.base

raise 'Read test failed' if result.NBases != 766

# Now write test SCF file
wresult = Biolib::Staden_io_lib.write_reading('test.scf', result, 0);
raise 'Write test failed' if wresult!=0 or !File.exist?('test.scf')
File.unlink('test.scf')

exit 0
