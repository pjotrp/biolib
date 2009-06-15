
require 'biolib/biolib_R'

result = Biolib::Biolib_R.BioLib_R_Init()

# test memory allocation

map = Biolib::Biolib_R.R_alloc(2,2)

# test native math functions

print "factorial(10): "
p Biolib::Biolib_R.Rf_gammafn(10+1)
print "Ggamma:\n"
p Biolib::Biolib_R.Rf_rgamma(0.5,2)
p Biolib::Biolib_R.Rf_gammafn(0.5)
print "log(2): "
p Biolib::Biolib_R.Rlog1p(1)

exit 0
