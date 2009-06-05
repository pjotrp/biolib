cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_affyio)

SET(LIBNAME biolib_affyio-${MAP_VERSION})

SET (M_NAME affyio)
SET (M_VERSION 1.8)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)

FIND_PACKAGE(Map REQUIRED)
FIND_PACKAGE(RLibs REQUIRED)
FIND_PACKAGE(ZLIB REQUIRED)

INCLUDE_DIRECTORIES(.)

BUILD_CLIB()

ADD_LIBRARY(${LIBNAME} SHARED
     biolib_affyio.c 
     read_abatch.c 
     read_cdf_xda.c 
     read_cdffile2.c 
     fread_functions.c 
     read_generic.c
     read_celfile_generic.c
)

# ---- The following may be required for OSX
TARGET_LINK_LIBRARIES(${LIBNAME} ${ZLIB_NAME})

INSTALL_CLIB()
