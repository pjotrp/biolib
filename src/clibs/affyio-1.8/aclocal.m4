##
## Try finding zlib library and headers
##
## R_ZLIB()
##
AC_DEFUN([R_ZLIB], [
  have_zlib=no
  AC_CHECK_LIB(z, main, [
    AC_CHECK_HEADER(zlib.h, [
      AC_MSG_CHECKING([if zlib version >= 1.1.3])
      AC_TRY_RUN([
#include "confdefs.h"
#include <string.h>
#include <zlib.h>
int main() {
#ifdef ZLIB_VERSION
  return(strcmp(ZLIB_VERSION, "1.1.3") < 0);
#else
  return(1);
#endif
}],     [AC_MSG_RESULT([yes])
          have_zlib=yes],
        AC_MSG_RESULT([no]),
        AC_MSG_RESULT([no]))
    ])
  ])
  if test "${have_zlib}" = yes; then
    AC_DEFINE(HAVE_ZLIB)
    LIBS='-lz '$LIBS
  fi
])

