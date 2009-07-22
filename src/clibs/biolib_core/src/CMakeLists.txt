cmake_minimum_required(VERSION 2.6)

SET(LIBNAME biolib_core-${MAP_VERSION})   # override

PROJECT(Biolib_core)
SET (M_NAME biolib_core)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)

FIND_PACKAGE(Map REQUIRED)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)

INCLUDE_DIRECTORIES(../include)

SET(LIBNAME biolib_core-${MAP_VERSION})   # override

BUILD_CLIB()

ADD_LIBRARY(${LIBNAME} SHARED biolib_error.c)

INSTALL_CLIB()
