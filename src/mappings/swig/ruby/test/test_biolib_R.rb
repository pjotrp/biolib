
require 'biolib/biolib_R'

result = Biolib::Biolib_R.BioLib_R_Init()

# test memory allocation

map = Biolib::Biolib_R.R_alloc(2,2)

# test native math functions

random = Biolib::Biolib_R.Rf_log(30)
p random

exit 0
