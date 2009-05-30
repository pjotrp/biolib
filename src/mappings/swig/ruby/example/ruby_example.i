%module example

/* This typemap for double** takes an array of Ruby values and turns it
 * into a C matrix, based on the number of rows and cols provided. The
 * matrix can be modified ans is returned from the method as an array again.
 *
 * Example:
 *   values = [1.1,1.2,2.1,2.2,3.1,3.2]
 *   result = Biolib::Example.matrix_as_array_change(2,3,values)
 *   raise "Test failed with value #{result}" if result[3] != 4
 */

%typemap(in) double **matrix_as_array {
   int cols = arg1;
   int rows = arg2;
   int i, row;
   int len;
   double *base;
   double **dptr;
   
   if (!rb_obj_is_kind_of($input,rb_cArray))
     rb_raise(rb_eArgError, "Expected Array of values for double **");
   len = rows * cols;
   /* len = RARRAY($input)->len; */
   dptr = (double **)malloc(rows*sizeof(double *));
   base = (double *)malloc(len*sizeof(double));
   for (i=0; i<len; i++)
     base[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
   for (row=0; row<rows; row++)
     dptr[row] = &base[row*cols];
   arg3 = dptr;
}

%typemap(argout) double **matrix_as_array {
    int i,j;
    int cols = arg1;
    int rows = arg2;

    /* example: printf("%f,%f",arg3[0][0],arg3[1][0]); */
    $result = rb_ary_new();
    for (i=0; i<rows; i++)
      for (j=0; j<cols; j++)
        rb_ary_push($result,rb_float_new(arg3[i][j]));
}

%typemap(freearg) double ** {
    int i;
    int rows = arg2;

    if ($1) {
      free(*$1);
      free($1);
    }
}
%include ../../example.i


