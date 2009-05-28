%module rqtl

%typemap(in) double * {
   int i;
   int len;
   
   if (!rb_obj_is_kind_of($input,rb_cArray))
     rb_raise(rb_eArgError, "Expected Array of values");
   len = RARRAY($input)->len;
   $1 = (double *)malloc(len*sizeof(double));
   for (i=0; i<len; ++i)
     ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
}

%typemap(freearg) double * {
    if ($1) free($1);
}   

void scanone_mr(int n_ind, int n_pos, int n_gen, int **Geno,
    double **Addcov, int n_addcov, double **Intcov,
    int n_intcov, double *pheno, double *weights,
    double *result);

%include ../../rqtl.i
