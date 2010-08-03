
print "PATH=",ENV['PATH'],"\n"
p $:

require 'biolib/samtools'

datadir = '../../../../test/data/samtools'
samgz = datadir+'/ex3.sam'
raise 'Error can not find '+samgz if !File.exist?(samgz)

fh = Biolib::Samtools.samopen(samgz,"r",nil)
# num,bam = Biolib::Samtools.samread(fh)
num,bam = Biolib::Samtools.samread(fh)
Biolib::Samtools.samclose(fh)

exit 0
