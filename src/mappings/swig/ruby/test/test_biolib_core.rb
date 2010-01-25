
require 'biolib/biolib_core'

Biolib::Biolib_core.biolib_setloglevel(7)
Biolib::Biolib_core.biolib_log(7,"Testing message at loglevel=7")
Biolib::Biolib_core.biolib_setloglevel(3)
# this message should not be visible:
Biolib::Biolib_core.biolib_log(7,"Testing message at loglevel=3")
Biolib::Biolib_core.biolib_log(Biolib::Biolib_core::LOG_ALERT,"Testing message at loglevel=2")
exit 0
