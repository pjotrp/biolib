# CMake script to locate external libraries for BioLib
#
# Using
#
#   USE_RLIB
#   USE_ZLIB
#   USE_BIOLIBCORE
#

# ---- Using libraries

IF(USE_RLIB)
  SET (USE_BIOLIBCORE TRUE)
  FIND_PACKAGE(RLibs)
ENDIF(USE_RLIB)

IF(USE_ZLIB)
  SET (USE_BIOLIBCORE TRUE)
  FIND_PACKAGE(ZLIB)
ENDIF(USE_ZLIB)

IF(USE_BIOLIBCORE)
  add_definitions(-DBIOLIB)
	INCLUDE_DIRECTORIES(${BIOLIB_CLIBS_PATH}/biolib_core/include)
	if(NOT BUILD_LIBS)
    FIND_LIBRARY(BIOLIB_LIBRARY NAMES libbiolib_core-${BIOLIB_VERSION}.so PATHS ${BIOLIB_CLIBS_PATH}/biolib_core/build)
	  message("Found ${BIOLIB_LIBRARY}")
  endif(NOT BUILD_LIBS)
ENDIF(USE_BIOLIBCORE)


