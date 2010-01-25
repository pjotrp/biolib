cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_affyio)

SET (M_NAME affyio)
SET (M_VERSION 1.8)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)

SET(USE_ZLIB TRUE)
SET(USE_RLIB TRUE)

FIND_PACKAGE(Map REQUIRED)
FIND_PACKAGE(MapLibraries REQUIRED)

INCLUDE_DIRECTORIES(.)

NAME_CLIB()

ADD_LIBRARY(${LIBNAME} SHARED
     biolib_affyio.c 
     read_abatch.c 
     read_cdf_xda.c 
     read_cdffile2.c 
     fread_functions.c 
     read_generic.c
     read_celfile_generic.c
)

BUILD_CLIB()

INSTALL_CLIB()
