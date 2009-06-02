%define BIOLIB_INARRAY(type,name)
  %typemap(in) type* name {
    /* %typemap(in) type* name */
    int i, num;
    
    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "Expected Array of values for $1_name");
    num = RARRAY($input)->len;
    $1 = (type *)malloc(num*sizeof(type));
    arg1 = num;
    for (i=0; i<num; ++i)
      ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
  }

  %typemap(freearg) type *name {
    /* %typemap(freearg) type *name */
    if ($1) free($1);
  }   
%enddef

/* The following typemaps turn a function with definition:
 *
 *    result = func(array)
 *
 * into a C call
 *
 *    func(num, type *data, type *result)
 *
 * where num is digested from the array size. Note that arg1 is still
 * used as a function wide parameter.
 */

%define BIOLIB_INOUTARRAY(type,num,data,result)
  %typemap(in, numinputs=0) int num {
    /* %typemap(in, numinputs=0) int num: ignore num input */
  }

  %typemap(in) (type* data, type *result) {
    /* %typemap(in) (type* data, type *result) */
    int i, asize;
    
    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "Expected Array of values for $1_name");
    asize = RARRAY($input)->len;
    $1 = (type *)malloc(asize*sizeof(type));
    arg1 = asize;
    for (i=0; i<asize; ++i)
      ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
    $2 = (type *)malloc(asize*sizeof(type));
  }

  %typemap(freearg) (type* data, type *result) {
    /* %typemap(in) (type* data, type *result) */
    if ($1) free($1);
    if ($2) free($2);
  }
%enddef

%define BIOLIB_OUTARRAY(type,result)
  /* Pass a result through an array pointer */

  %typemap(out) type *result {
    /* %typemap(out) type *result: ignore */
  }

  %typemap(argout) type *result {
    /* %typemap(argout) type *result */
    int i;
    int num = arg1;

    /* example: printf("%f,%f",$1[0][0],$1[1][0]); */
    $result = rb_ary_new();
    for (i=0; i<num; i++)
      rb_ary_push($result,rb_float_new($1[i]));
  }

  %typemap(freearg) type *result {
    /* %typemap(freearg) type *result */
    if ($1) free($1);
  }   
%enddef

