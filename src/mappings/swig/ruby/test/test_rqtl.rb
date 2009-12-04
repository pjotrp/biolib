
require 'biolib/rqtl'

if $0 == __FILE__
  # FIXME: this empty function succeeds because it does not need
  # Rlib functions. Anything more elaborate would need to initialize
  # Rlib first.

  CRIL = 'R'
  MAA  = '0'

  prob = Biolib::Rqtl.start_prob(CRIL,MAA);

  raise "Error" if prob != 0.5

  res = Biolib::Rqtl.scanone_mr(0,0,0,[],[],0,[],0,[],[])
  print "prob = #{prob}, result = #{res}"
  print "Success!"
  exit 0
end
