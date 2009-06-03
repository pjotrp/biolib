%module example

%include ../../typemaps/ruby/biolib_matrix.i

MAP_INOUT_DIM_MATRIXASARRAY(double,arg1,arg2,matrix_as_array)

%include ../../typemaps/ruby/biolib_array.i

MAP_INOUT_ARRAY(double,data,result) 

%include ../../example.i


