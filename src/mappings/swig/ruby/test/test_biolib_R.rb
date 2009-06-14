
require 'biolib/biolib_R'

result = Biolib::Biolib_R.BioLib_R_Init()

# test memory allocation

map = Biolib::Biolib_R.R_alloc(2,2)

exit 0
