%module rqtl

/* Default conversion of Ruby NumArray to double pointer */
%typemap(in) double * {
   int i;
   int len;
   
   if (!rb_obj_is_kind_of($input,rb_cArray))
     rb_raise(rb_eArgError, "Expected Array of values for double *");
   len = RARRAY($input)->len;
   $1 = (double *)malloc(len*sizeof(double));
   for (i=0; i<len; ++i)
     ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
}

%typemap(freearg) double * {
    if ($1) free($1);
}   

/* Set the input argument to point to a temporary variable */
%typemap(in, numinputs=0) double *result {
   $1 = (double *)malloc(100000*sizeof(double));
}

%typemap(out) double *result {
}

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

%typemap(in) int ** (int n_ind, int n_pos) {
   int i;
   int len;
   int *base;
   
   if (!rb_obj_is_kind_of($input,rb_cArray))
     rb_raise(rb_eArgError, "Expected Array of values for int **");
   len = RARRAY($input)->len;
   $1 = (int **)malloc(n_pos*sizeof(int *));
   base = (int *)malloc(n_ind*n_pos*sizeof(int));
   /* 
      FIX: A 32 bit system will most likely have 32 bit integers, so the 
      largest value is 4,294,967,296 - a number we will soon reach for GG 
   */
   for (i=0; i<len; ++i)
     base[i] = rb_num2int(RARRAY($input)->ptr[i]);
   /* markers.size rows of individuals */
   for (i=0; i<n_pos; i++)
     $1[i] = &base[i*n_ind];
}

%typemap(freearg) int ** {
    /* FIX memory leak here */
    if ($1) free($1);
}

%typemap(in) double ** {
   int i;
   int len;
   double *base;
   /* FIX: for now assume covariates is 0 */
   if (!rb_obj_is_kind_of($input,rb_cArray))
     rb_raise(rb_eArgError, "Expected Array of values for double **");
   len = RARRAY($input)->len;
   $1 = NULL;
   /* $1 = (double **)malloc(len*sizeof(double *));
   for (i=0; i<len; ++i)
     *($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
   */
}

%typemap(freearg) double ** {
    /* FIX memory leak here */
    if ($1) free($1);
}

%include ../../rqtl.i
