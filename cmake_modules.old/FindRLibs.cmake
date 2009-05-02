# - Find R libraries - much simplified and works with NIX
#
# This module finds if R is installed and determines where the include files
# and libraries are. It also determines what the name of the library is. This
# code sets the following variables:
#
#  R_INCLUDE_PATH = path to where R.h is found
#  R_EXECUTABLE   = full path to the R binary

FIND_PROGRAM(R_EXECUTABLE R)

IF(R_EXECUTABLE)
  GET_FILENAME_COMPONENT(R_BINPATH ${R_EXECUTABLE} PATH)  
  GET_FILENAME_COMPONENT(R_PATH ${R_BINPATH} PATH)  
	SET(R_LIBRARY ${R_PATH}/lib/R/lib/libR.so)
	SET(R_LIKELY_INCLUDE_PATH ${R_PATH}/lib/R/include)
ENDIF(R_EXECUTABLE)

# ---- Find R.h
SET(R_POSSIBLE_INCLUDE_PATHS
  /usr/share/R/include
)
FIND_PATH(R_INCLUDE_PATH R.h
  ${R_LIKELY_INCLUDE_PATH}
  ${R_POSSIBLE_INCLUDE_PATHS}
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(RLibs DEFAULT_MSG R_LIBRARY R_INCLUDE_PATH)

GET_FILENAME_COMPONENT(R_LIBRARY_PATH ${R_LIBRARY} PATH)  

FIND_LIBRARY(RBLAS_LIBRARY NAMES libRblas.so PATHS 
  ${R_LIBRARY_PATH}
)


MESSAGE("R_EXECUTABLE=${R_EXECUTABLE}")
MESSAGE("R_INCLUDE_PATH=${R_INCLUDE_PATH}")
MESSAGE("R_LIBRARY=${R_LIBRARY}")
MESSAGE("RBLAS_LIBRARY=${RBLAS_LIBRARY}")

if(NOT EXISTS ${R_LIBRARY})
	message(FATAL_ERROR "${R_LIBRARY} was not found (has R been built as shared library libR.so?)")
endif(NOT EXISTS ${R_LIBRARY})

MARK_AS_ADVANCED(
  R_INCLUDE_PATH
  R_EXECUTABLE
  R_LIBRARY
  )
