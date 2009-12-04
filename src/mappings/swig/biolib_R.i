#define HAVE_LOG1P 1
#define HAVE_EXPM1 1

%{
  #include <biolib_R_map.h>
  #include <Rconfig.h>
  #include <R_ext/RS.h>
  #include <R_ext/Memory.h>

  #include <R_ext/Utils.h>
  #include <Rmath.h>
%}

%include <biolib_R_map.h>
%include <Rconfig.h>
%include <R_ext/RS.h>
%include <R_ext/Memory.h>
%include <R_ext/Utils.h>
%include <Rmath.h>

double  log1p(double);
double  expm1(double);
