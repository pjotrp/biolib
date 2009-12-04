%module example

/*
void scanone_mr(int n_ind, int n_pos, int n_gen, int **Geno,
                double **Addcov, int n_addcov, double **Intcov,
                int n_intcov, double *pheno, double *weights,
                double *result);
*/

%include ../../typemaps/ruby/biolib_matrix.i

MAP_IN_DIM_MATRIXASARRAY(int,0,1,Geno) /* Dimensions from 0 and 1 parameter */
MAP_IN_DIM_MATRIXASARRAY(double,5,0,Addcov)
MAP_IN_DIM_MATRIXASARRAY(double,7,0,Intcov)

MAP_INOUT_DIM_MATRIXASARRAY(double,0,1,matrix_as_array)

%include ../../typemaps/ruby/biolib_array.i

MAP_IN_DIM_ARRAY(double,0,weights)
MAP_IN_DIM_ARRAY(double,0,pheno)
MAP_OUT_DIM_ARRAY(double,1,result)

MAP_INOUT_ARRAY(double,data,result) 
MAP_IN_ARRAY(double,data1) 
MAP_OUT_ARRAY(double,result1) 

MAP_IN_DIM_ARRAY(double,0,data2) 
MAP_OUT_DIM_ARRAY(double,0,result2) 

MAP_IN_ARRAY(double,data3) 
MAP_OUT_DIM_ARRAY(double,0,result3) 

%include ../../example.i


