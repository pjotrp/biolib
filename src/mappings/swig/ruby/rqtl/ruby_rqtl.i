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

BIOLIB_INMATRIXASARRAY(int,arg2,arg1,Geno) 
BIOLIB_INMATRIXASARRAY(double,arg6,arg1,Addcov)
BIOLIB_INMATRIXASARRAY(double,arg8,arg1,Intcov)

%include ../../typemaps/ruby/biolib_array.i

/* BIOLIB_INARRAY(double,weights) 
BIOLIB_INARRAY(double,pheno) 
*/

/* BIOLIB_INOUTARRAY(double,n_ind,pheno,result) 
 */

BIOLIB_OUTARRAY(double,arg1,result)

%include ../../rqtl.i
