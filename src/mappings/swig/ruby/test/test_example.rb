
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
# result = Biolib::Example.array_transform_to_result1([1,2,3,4],[0,0,0,0])
# raise "Test failed with value #{result}" if result[3] != 5.5
result = Biolib::Example.array_transform_to_result2(4,[1,2,3,4])
raise "Test failed with value #{result}" if result[3] != 6
result = Biolib::Example.array_transform_to_result3(4,[1,2,3,4])
raise "Test failed with value #{result}" if result[3] != 6.5
#           i1,i2
genotypes = [1,2,
             3,4,
             5,6]
phenotypes = [1.0,2.0]
weights = [1.0,1.0]
result = Biolib::Example.scanone_mr(2,3,6,genotypes,[],0,[1.0,1.0],1,phenotypes,weights)
raise "Test failed with value #{result}" if result != [ 6.0, 1.0, 3.0 ]

exit 0
