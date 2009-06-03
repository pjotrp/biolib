
%define MAP_IN_DIM_ARRAY(type,sizearg,name)
  %typemap(in) type* name {
    /* MAP_IN_DIM_ARRAY %typemap(in) type* name */
    int i, asize;
    
    SWIG_AsVal_int(argv[sizearg], &asize);

    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "MAP_IN_ARRAY expected Array of values for $1_name");
    asize = sizearg;
    $1 = (type *)malloc(asize*sizeof(type));
    for (i=0; i<asize; ++i)
      ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
  }

  %typemap(freearg) type *name {
    /* MAP_IN_DIM_ARRAY %typemap(freearg) type *name */
    if ($1) free($1);
  }   
%enddef

%define MAP_IN_ARRAY(type,name)
  %typemap(in) type* name {
    /* MAP_IN_ARRAY %typemap(in) type* name */
    int i, len;
    
    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "MAP_IN_ARRAY expected Array of values for $1_name");
    len = RARRAY($input)->len;
    $1 = (type *)malloc(len*sizeof(type));
    for (i=0; i<len; ++i)
      ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
  }

  %typemap(freearg) type *name {
    /* MAP_IN_ARRAY %typemap(freearg) type *name */
    if ($1) free($1);
  }   
%enddef

/* The following typemaps turn a function with definition:
 *
 *    result = func(array)
 *
 * into a C call
 *
 *    func(len, type *data, type *result)
 *
 * where len is digested from the array size. Note that arg1 is still
 * used as a function wide parameter.
 */

%define MAP_INOUT_DIM_ARRAY(type,sizearg,data,result)

  %typemap(in) (type* data, type *result) {
    /* MAP_INOUT_DIM_ARRAY %typemap(in) (type* data, type *result) */
    int i, asize;
    
    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "MAP_INOUT_DIM_ARRAY expected Array of values for $1_name");
    SWIG_AsVal_int(argv[sizearg], &asize);

    $1 = (type *)malloc(asize*sizeof(type));
    for (i=0; i<asize; ++i)
      ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
    $2 = (type *)malloc(asize*sizeof(type));
  }

  %typemap(freearg) (type* data, type *result) {
    /* MAP_INOUT_DIM_ARRAY %typemap(in) (type* data, type *result) */
    if ($1) free($1);
    if ($2) free($2);
  }
%enddef

%define MAP_INOUT_ARRAY(type,data,result)

  %typemap(in) (int num, type* data, type *result) {
    /* MAP_INOUT_ARRAY %typemap(in) (int, type* data, type *result) */
    int i, asize;
    
    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "MAP_INOUT_ARRAY expected Array of values for $2_name");
    asize = RARRAY($input)->len;
    $1 = asize;
    $2 = (type *)malloc(asize*sizeof(type));
    for (i=0; i<asize; ++i)
      ($2)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
    $3 = (type *)malloc(asize*sizeof(type));
  }

  %typemap(argout) (int num, type *data, type *result) {
    /* MAP_INOUT_ARRAY %typemap(argout) int type, *data type, *result */
    int i;
    
    int asize = RARRAY($input)->len;
    /* example: printf("%f,%f",$1[0][0],$1[1][0]); */
    $result = rb_ary_new();
    for (i=0; i<asize; i++)
      rb_ary_push($result,rb_float_new($3[i]));
  }

  %typemap(freearg) (int num, type* data, type *result) {
    /* MAP_INOUT_ARRAY %typemap(in) (int, type* data, type *result) */
    if ($2) free($2);
    if ($3) free($3);
  }
%enddef

%define MAP_OUT_DIM_ARRAY(type,sizearg,result)
  /* Pass a result through an array pointer */

  %typemap(in) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(in) type *result: ignore */
  }

  %typemap(out) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(out) type *result: ignore */
  }

  %typemap(argout) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(argout) type *result */
    int i, asize;

    SWIG_AsVal_int(argv[sizearg], &asize);
    /* example: printf("%f,%f",$1[0][0],$1[1][0]); */
    $result = rb_ary_new();
    for (i=0; i<asize; i++)
      rb_ary_push($result,rb_float_new($1[i]));
  }

  %typemap(freearg) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(freearg) type *result */
    if ($1) free($1);
  }   
%enddef

