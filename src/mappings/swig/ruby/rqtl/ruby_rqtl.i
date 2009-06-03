%module rqtl

/* R/qtl has some matrix parameters. These should be allocated too. 
   For example in

   void scanone_mr(int n_ind, int n_pos, int n_gen, int **Geno,
     double **Addcov, int n_addcov, double **Intcov,
     int n_intcov, double *pheno, double *weights,
     double *result);

   The passed in matrix is actually one array of values - also R/qtl references
   internally by matrix type - the parameters should actually be: 

     int const Geno[][]
*/

%include ../../typemaps/ruby/biolib_matrix.i

MAP_IN_DIM_MATRIXASARRAY(int,arg2,arg1,Geno) 
MAP_IN_DIM_MATRIXASARRAY(double,arg6,arg1,Addcov)
MAP_IN_DIM_MATRIXASARRAY(double,arg8,arg1,Intcov)

%include ../../typemaps/ruby/biolib_array.i

MAP_IN_ARRAY(double,weights)
MAP_IN_ARRAY(double,pheno) 

/* MAP_INOUTARRAY(double,n_ind,pheno,result) 
 */

MAP_OUT_DIM_ARRAY(double,arg1,result)

%include ../../rqtl.i
