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

MAP_IN_DIM_MATRIXASARRAY(int,0,1,Geno) 
MAP_IN_DIM_MATRIXASARRAY(double,5,0,Addcov)
MAP_IN_DIM_MATRIXASARRAY(double,7,0,Intcov)

%include ../../typemaps/ruby/biolib_array.i

MAP_IN_DIM_ARRAY(double,1,weights)
MAP_IN_DIM_ARRAY(double,0,pheno) 

/* MAP_INOUTARRAY(double,n_ind,pheno,result) 
 */

MAP_OUT_DIM_ARRAY(double,1,result)

%include ../../rqtl.i
