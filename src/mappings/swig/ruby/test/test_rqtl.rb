
require 'biolib/rqtl'

if $0 == __FILE__

  res = Biolib::Rqtl.scanone_mr(0,0,0,nil,nil,0,nil,0,[],[],[])
  print "result = #{res}"
  print "Success!"
  exit 0
end
