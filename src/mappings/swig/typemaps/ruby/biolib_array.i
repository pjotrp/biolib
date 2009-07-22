/* 
 * SWIG macro's for mapping C arrays (like double *). The coding is:
 *
 *   IN:    input array
 *   OUT:   output array (does not show in parameter list)
 *   INOUT: combination of above
 *   DIM:   takes the dimension from the argument list (the sizearg's)
 *
 */

%define MAP_IN_DIM_ARRAY(type,sizearg,name)
  %typemap(in) type *name {
    int i,asize;
    /* MAP_IN_DIM_ARRAY %typemap(in) type *name: ignore */
    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "MAP_IN_ARRAY expected Array of values for $1_name");
    SWIG_AsVal_int(argv[sizearg], &asize);
    $1 = (type *)malloc(asize*sizeof(type));
    if (RARRAY($input)->len != asize)
      rb_raise(rb_eArgError, "Array size incorrect for type **$1_name");
    for (i=0; i<asize; ++i)
      ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
  }

  %typemap(freearg) type *name {
    /* MAP_IN_DIM_ARRAY %typemap(freearg) type *name */
    if ($1) free($1);
  }   
%enddef

%define MAP_IN_DIM2_ARRAY(type,sizearg1,sizearg2,name)
  %typemap(in) type **name {
    int i,dim1,dim2,asize;
    /* MAP_IN_DIM2_ARRAY %typemap(in) type **name: ignore */
    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "MAP_IN_ARRAY expected Array of values for $1_name");
    SWIG_AsVal_int(argv[sizearg1], &dim1);
    SWIG_AsVal_int(argv[sizearg2], &dim2);

    asize = dim1*dim2;
    $1 = (type **)malloc(asize*sizeof(type));
    if (RARRAY($input)->len != asize)
      rb_raise(rb_eArgError, "Array size incorrect for type **$1_name");
    for (i=0; i<asize; ++i)
      ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
  }

  %typemap(freearg) type **name {
    /* MAP_IN_DIM2_ARRAY %typemap(freearg) type *name */
    if ($1) free($1);
  }   
%enddef

%define MAP_IN_DIM2_ARRAY1(type,sizearg1,sizearg2,name)
  %typemap(in) type *name {
    int i,dim1,dim2,asize;
    /* MAP_IN_DIM2_ARRAY1 %typemap(in) type *name: ignore */
    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "MAP_IN_ARRAY expected Array of values for $1_name");
    SWIG_AsVal_int(argv[sizearg1], &dim1);
    SWIG_AsVal_int(argv[sizearg2], &dim2);

    asize = dim1*dim2;
    $1 = (type *)malloc(asize*sizeof(type));
    if (RARRAY($input)->len != asize)
      rb_raise(rb_eArgError, "Array size incorrect for type **$1_name");
    for (i=0; i<asize; ++i)
      ($1)[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
  }

  %typemap(freearg) type *name {
    /* MAP_IN_DIM2_ARRAY1 %typemap(freearg) type *name */
    if ($1) free($1);
  }   
%enddef

%define MAP_IN_DIM3_ARRAY(type,sizearg1,sizearg2,sizearg3,name)
  %typemap(in) type ***name {
    int i,dim1,dim2,dim3,asize;
    int *base;
    /* MAP_IN_DIM3_ARRAY %typemap(in) type ***name: ignore */
    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "MAP_IN_ARRAY expected Array of values for $1_name");
    SWIG_AsVal_int(argv[sizearg1], &dim1);
    SWIG_AsVal_int(argv[sizearg2], &dim2);
    SWIG_AsVal_int(argv[sizearg2], &dim3);

    asize = dim1*dim2*dim3;
    $1 = (type ***)malloc(asize*sizeof(type));
    base = (int *)$1;
    if (RARRAY($input)->len != asize)
      rb_raise(rb_eArgError, "Array size incorrect for type **$1_name");
    for (i=0; i<asize; ++i)
      base[i] = rb_num2dbl(RARRAY($input)->ptr[i]);
  }

  %typemap(freearg) type ***name {
    /* MAP_IN_DIM3_ARRAY %typemap(freearg) type *name */
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
    if (RARRAY($input)->len != len)
      rb_raise(rb_eArgError, "Array size incorrect for type **$1_name");
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
    if (RARRAY($input)->len != asize)
      rb_raise(rb_eArgError, "Array size incorrect for type **$1_name");
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
    if (RARRAY($input)->len != asize)
      rb_raise(rb_eArgError, "Array size incorrect for type **$1_name");
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

  %typemap(in,numinputs=0) type *result {
    int asize;
    /* MAP_OUT_DIM_ARRAY %typemap(in) type *result: ignore */
    SWIG_AsVal_int(argv[sizearg], &asize);
    $1 = (type *)malloc(asize*sizeof(type));
  }

  %typemap(out) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(out) type *result: ignore */
  }

  %typemap(argout) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(argout) type *result */
    int i, asize;

    SWIG_AsVal_int(argv[sizearg], &asize);
    /* example: printf("%f,%f",$1[0][0],$1[1][0]); */
    vresult = rb_ary_new();
    for (i=0; i<asize; i++)
      rb_ary_push(vresult,rb_float_new($1[i]));
  }

  %typemap(freearg) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(freearg) type *result */
    if ($1) free($1);
  }   
%enddef

%define MAP_OUT_DIM2_ARRAY(type,sizearg1,sizearg2,result)
  /* Pass a result through an array pointer */

  %typemap(in,numinputs=0) type **result {
    int dim1,dim2,asize;
    /* MAP_OUT_DIM2_ARRAY %typemap(in) type *result: ignore */
    SWIG_AsVal_int(argv[sizearg1], &dim1);
    SWIG_AsVal_int(argv[sizearg2], &dim2);
    asize = dim1*dim2;
    $1 = (type **)malloc(asize*sizeof(type));
  }

  %typemap(out) type **result {
    /* MAP_OUT_DIM2_ARRAY %typemap(out) type *result: ignore */
  }

  %typemap(argout) type **result {
    /* MAP_OUT_DIM2_ARRAY %typemap(argout) type *result */
    int i,dim1,dim2,asize;
    type *base;
    SWIG_AsVal_int(argv[sizearg1], &dim1);
    SWIG_AsVal_int(argv[sizearg2], &dim2);
    asize = dim1*dim2;
    vresult = rb_ary_new();
    base = (type *)$1;
    for (i=0; i<asize; i++)
      rb_ary_push(vresult,rb_float_new(base[i]));
  }

  %typemap(freearg) type **result {
    /* MAP_OUT_DIM2_ARRAY %typemap(freearg) type *result */
    if ($1) free($1);
  }   
%enddef

%define MAP_OUT_DIM3_ARRAY1(type,sizearg1,sizearg2,sizearg3,result)
  /* Pass a result through an array pointer */

  %typemap(in,numinputs=0) type *result {
    int dim1,dim2,dim3,asize;
    /* MAP_OUT_DIM_ARRAY %typemap(in) type *result: ignore */
    SWIG_AsVal_int(argv[sizearg1], &dim1);
    SWIG_AsVal_int(argv[sizearg2], &dim2);
    SWIG_AsVal_int(argv[sizearg3], &dim3);
    asize = dim1*dim2*dim3;
    $1 = (type *)malloc(asize*sizeof(type));
  }

  %typemap(out) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(out) type *result: ignore */
  }

  %typemap(argout) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(argout) type *result */
    int i,dim1,dim2,dim3,asize;
    SWIG_AsVal_int(argv[sizearg1], &dim1);
    SWIG_AsVal_int(argv[sizearg2], &dim2);
    SWIG_AsVal_int(argv[sizearg3], &dim3);
    asize = dim1*dim2*dim3;
    vresult = rb_ary_new();
    for (i=0; i<asize; i++)
      rb_ary_push(vresult,rb_float_new($1[i]));
  }

  %typemap(freearg) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(freearg) type *result */
    if ($1) free($1);
  }   
%enddef

%define MAP_OUT_ARRAY(type,result)
  /* Pass a result through an array pointer */

  %typemap(in) (type *result) {
    int asize;
    /* MAP_OUT_ARRAY %typemap(in) type *result: ignore */
    int i, len;
    if (!rb_obj_is_kind_of($input,rb_cArray))
      rb_raise(rb_eArgError, "MAP_OUT_ARRAY expected Array of values for $1_name");
    len = RARRAY($input)->len;
    $1 = (type *)malloc(len*sizeof(type));
  }

  %typemap(out) type *result {
    /* MAP_OUT_ARRAY %typemap(out) type *result: ignore */
  }

  %typemap(argout) type *result {
    /* MAP_OUT_ARRAY %typemap(argout) type *result */
    int i, len;
    len = RARRAY($input)->len;

    vresult = rb_ary_new();
    for (i=0; i<len; i++)
      rb_ary_push(vresult,rb_float_new($1[i]));
  }

  %typemap(freearg) type *result {
    /* MAP_OUT_DIM_ARRAY %typemap(freearg) type *result */
    if ($1) free($1);
  }   
%enddef

