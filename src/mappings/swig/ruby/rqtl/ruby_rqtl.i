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

/* for scanone */

/*
void scanone_mr(int n_ind, int n_pos, int n_gen, int **Geno,
                double **Addcov, int n_addcov, double **Intcov,
                int n_intcov, double *pheno, double *weights,
                double *result);
*/

%include ../../typemaps/ruby/biolib_matrix.i

MAP_IN_DIM_MATRIXASARRAY(int,0,1,Geno)
MAP_IN_DIM_MATRIXASARRAY(double,5,0,Addcov)
MAP_IN_DIM_MATRIXASARRAY(double,7,0,Intcov)

%include ../../typemaps/ruby/biolib_array.i

MAP_IN_DIM_ARRAY(double,0,weights)
MAP_IN_DIM_ARRAY(double,0,pheno)
MAP_OUT_DIM_ARRAY(double,1,result)

%include <scanone_mr.h>
/*
void scanone_imp(int n_ind, int n_pos, int n_gen, int n_draws,
                 int ***Draws, double **Addcov, int n_addcov,
                 double **Intcov, int n_intcov, double *pheno,
                 int nphe, double *weights,
                 double **Result);
*/

MAP_IN_DIM3_ARRAY(int,0,1,4,Draws)     /* Geno[mar][ind] */
MAP_IN_DIM_MATRIXASARRAY(double,7,0,Addcov)
MAP_IN_DIM_MATRIXASARRAY(double,9,0,Intcov)
MAP_OUT_DIM2_ARRAY(double,1,11,Result)

%include <scanone_imp.h>
/* For sim_geno_f2 */

/* void sim_geno_f2(int *n_ind, int *n_pos, int *n_draws, int *geno, double *rf, double *error_prob, int *draws); */

%include typemaps.i
%apply int *INPUT { int *n_ind, int *n_pos, int *n_draws };
%apply double *INPUT { double *error_prob };

MAP_IN_DIM2_ARRAY1(int,0,1,geno)     /* Geno[mar][ind] */
MAP_IN_DIM_ARRAY(double,1,rf)       /* recombination frequencies n_pos-2 */
MAP_OUT_DIM3_ARRAY1(int,0,1,2,draws) /* Draws[repl][mar][ind] */

%include <hmm_f2.h>
%include ../../rqtl.i

