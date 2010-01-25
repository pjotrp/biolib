// Mapping R functions to biolib - used for porting R modules into
// biolib.
//

#ifdef __cplusplus
extern "C" {
#endif

// #ifdef BIOLIB

  // #include <biolib_error.h>

  // Redefine the R error function FIXME: Remu?
  // #undef error
  // #define error(args...) biolib_fatal(args)

  void BioLib_R_Init();
  void BioLib_R_Close();

// #endif // BIOLIB
#ifdef __cplusplus
  } 
#endif

