
print "PATH=",ENV['PATH'],"\n"
p $:

require 'biolib/samtools'

datadir = '../../../../test/data/samtools'
samgz = datadir+'/ex1.sam.gz'
raise 'Error can not find '+samgz if !File.exist?(samgz)

result = Biolib::Samtools.samopen(samgz,"r",nil)

exit 0
