cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_affyio)

IF(NOT BUILD_LIBS)
  SET (CMAKE_MODULE_PATH ../../../../cmake_modules)
ENDIF(NOT BUILD_LIBS)

FIND_PACKAGE(RLibs)
FIND_PACKAGE(BioLib)
FIND_PACKAGE(ZLIB)

SET(LIBNAME biolib_affyio-${BIOLIB_VERSION})

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${R_INCLUDE_PATH})

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)

ADD_LIBRARY(${LIBNAME} SHARED
     biolib_affyio.c 
     read_abatch.c 
     read_cdf_xda.c 
     read_cdffile2.c 
     fread_functions.c 
     read_generic.c
     read_celfile_generic.c
)

INSTALL(TARGETS ${LIBNAME}
  LIBRARY DESTINATION lib
)

