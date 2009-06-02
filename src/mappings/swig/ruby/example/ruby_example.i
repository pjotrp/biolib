%module example

%include ../../typemaps/ruby/biolib_datap_resultp.i
%include ../../typemaps/ruby/biolib_resultp.i
%include ../../typemaps/ruby/biolib_matrix.i

BIOLIB_INARRAY(double, data)
BIOLIB_INOUTARRAY(double,num,data,result)

%include ../../example.i


