%module example

%include ../../typemaps/ruby/biolib_matrix.i
%include ../../typemaps/ruby/biolib_array.i

BIOLIB_INARRAY(double, data)
BIOLIB_INOUTARRAY(double,num,data,result)
BIOLIB_OUTARRAY(double,result)
BIOLIB_INMATRIXASARRAY(double,arg1,arg2,matrix_as_array)

%include ../../example.i


