// Mapping R functions to biolib - used for porting R modules into
// biolib.
//

#ifdef BIOLIB

  #include <biolib_error.h>

  // Redefine the R error function
  #undef error
  #define error(args...) biolib_fatal(args)

#endif // BIOLIB
