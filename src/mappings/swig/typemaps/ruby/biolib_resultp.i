/* Pass a result through an array pointer */

%typemap(out) double *result {
  /* %typemap(out) double *result: ignore */
}

%typemap(argout) double *result {
  /* %typemap(argout) double *result */
  int i;
  int num = arg1;

  /* example: printf("%f,%f",$1[0][0],$1[1][0]); */
  $result = rb_ary_new();
  for (i=0; i<num; i++)
    rb_ary_push($result,rb_float_new($1[i]));
}

%typemap(freearg) double *result {
  /* %typemap(freearg) double *result */
  if ($1) free($1);
}   


