
require 'biolib/rqtl'

if $0 == __FILE__
  # FIXME: this empty function succeeds because it does not need
  # Rlib functions. Anything more elaborate would need to initialize
  # Rlib first.
  res = Biolib::Rqtl.scanone_mr(0,0,0,[],[],0,[],0,[],[])
  print "result = #{res}"
  print "Success!"
  exit 0
end
