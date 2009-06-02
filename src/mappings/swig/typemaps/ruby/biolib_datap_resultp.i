/* The following typemaps turn a function with definition:
 *
 *    result = func(array)
 *
 * into a C call
 *
 *    func(num, double *data, double *result)
 *
 * where num is digested from the array size. Note that arg1 is still
 * used as a function wide parameter.
 */

%typemap(in, numinputs=0) int num {
  /* %typemap(in, numinputs=0) int num: ignore num input */
}

%typemap(in) (double* data, double *result) {
  /* %typemap(in) (double* data, double *result) */
  int i, num;
  
  if (!rb_obj_is_kind_of($input,rb_cArray))
    rb_raise(rb_eArgError, "Expected Array of values for $1_name");
  num = RARRAY($input)->len;
  $1 = (double *)malloc(num*sizeof(double));
  arg1 = num;
  for (i=0; i<num; ++i)
    ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
  $2 = (double *)malloc(num*sizeof(double));
}

%typemap(freearg) (double* data, double *result) {
  /* %typemap(in) (double* data, double *result) */
  if ($1) free($1);
  if ($2) free($2);
}

%typemap(in) double* data {
  /* %typemap(in) double* data */
  int i, num;
  
  if (!rb_obj_is_kind_of($input,rb_cArray))
    rb_raise(rb_eArgError, "Expected Array of values for $1_name");
  num = RARRAY($input)->len;
  $1 = (double *)malloc(num*sizeof(double));
  arg1 = num;
  for (i=0; i<num; ++i)
    ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
}

%typemap(freearg) double *data {
  /* %typemap(freearg) double *data */
  if ($1) free($1);
}   


