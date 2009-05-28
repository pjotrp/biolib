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

/* R/qtl has some matrix parameters. These should be allocated too. 
   For example in

   void scanone_mr(int n_ind, int n_pos, int n_gen, int **Geno,
     double **Addcov, int n_addcov, double **Intcov,
     int n_intcov, double *pheno, double *weights,
     double *result);

   The passed in matrix is actually one array of values.
*/

%typemap(in) int ** {
   int i;
   int len;
   
   if (!rb_obj_is_kind_of($input,rb_cArray))
     rb_raise(rb_eArgError, "Expected Array of values for int **");
   len = RARRAY($input)->len;
   $1 = (int **)malloc(len*sizeof(int));
   for (i=0; i<len; ++i)
     *($1)[i] = rb_num2int(RARRAY($input)->ptr[i]);
}

%typemap(freearg) int ** {
    if ($1) free($1);
}

%typemap(in) double ** {
   int i;
   int len;
   
   if (!rb_obj_is_kind_of($input,rb_cArray))
     rb_raise(rb_eArgError, "Expected Array of values for double **");
   len = RARRAY($input)->len;
   $1 = (double **)malloc(len*sizeof(double));
   for (i=0; i<len; ++i)
     *($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
}

%typemap(freearg) double ** {
    if ($1) free($1);
}

%typemap(out) double * result {
}

%include ../../rqtl.i
