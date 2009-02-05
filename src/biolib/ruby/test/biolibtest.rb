# Support for unit testing Biolib
#
# Large files are not stored in the source tree, but are fetched from
# a central repository on demand (for unit testing).

module BiolibTest

  DATA_REPOSITORY = 'http://bio3.biobeat.org/download/biolib/data/'

  # Fetch and unzip files for unit testing. Uses wget and zcat.
  def BiolibTest::fetch fn, unzip=false
    tmpdir = '/tmp' # Dir.tmpdir
    base   = File.basename(fn)
    downloadfn  = File.join(tmpdir,base)
    if !File.exist?(downloadfn)
      # fetch it
      print `wget -O #{downloadfn} #{DATA_REPOSITORY+base}`
    end
    newfn = downloadfn
    if unzip
      newfn = downloadfn.sub(/\.gz$/,'')
      print `zcat #{downloadfn} > #{newfn}`
    end
    print newfn+' '+`ls -l #{newfn}`
    newfn
  end

end
