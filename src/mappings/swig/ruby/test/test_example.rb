
require 'biolib/example'

result = Biolib::Example.my_mod(7,3)
print "Biolib::Example.my_mod(7,3) renders #{result}\n"
raise 'Test failed' if result != 1
exit 0
