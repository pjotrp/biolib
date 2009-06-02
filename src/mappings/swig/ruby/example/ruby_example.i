%module example

%include ../../typemaps/ruby/biolib_matrix.i
%include ../../typemaps/ruby/biolib_array.i

BIOLIB_INARRAY(double, data)
BIOLIB_INOUTARRAY(double,num,data,result)
BIOLIB_OUTARRAY(double,result)

%include ../../example.i


