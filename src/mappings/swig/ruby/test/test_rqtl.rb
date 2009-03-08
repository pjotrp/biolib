
require 'biolib/rqtl'

if $0 == __FILE__

  Biolib::Rqtl.R_scanone_mr()
  print "Success!"
  exit 0
end
