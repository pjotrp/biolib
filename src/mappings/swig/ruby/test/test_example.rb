
require 'biolib/example'

result = Biolib::Example.my_mod(7,3)
print "Biolib::Example.my_mod(7,3) renders #{result}\n"
raise 'Test failed' if result != 1

values = [1.1,1.2,2.1,2.2,3.1,3.2]
result = Biolib::Example.matrix_as_array_change(2,3,values)
p values
raise "Test failed with value #{result}" if result[3] != 4

result = Biolib::Example.array_transform_to_result([1,2,3,4])
raise "Test failed with value #{result}" if result[3] != 5
exit 0
