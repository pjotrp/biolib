%module example

%include ../../typemaps/ruby/biolib_matrix.i

MAP_INOUT_DIM_MATRIXASARRAY(double,0,1,matrix_as_array)

%include ../../typemaps/ruby/biolib_array.i

MAP_INOUT_ARRAY(double,data,result) 
MAP_IN_ARRAY(double,data1) 
MAP_OUT_ARRAY(double,result1) 

MAP_IN_DIM_ARRAY(double,0,data2) 
MAP_OUT_DIM_ARRAY(double,0,result2) 

%include ../../example.i


