cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_core)
SET (M_NAME biolib_core)

IF(NOT BUILD_LIBS)
  # Building in a local module: Set the module search path manually
  SET (MAP_ROOT ../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
  IF(NOT IS_DIRECTORY ${CMAKE_MODULE_PATH})
    MESSAGE(FATAL_ERROR "Can not find BioLib context")
  ENDIF(NOT IS_DIRECTORY ${CMAKE_MODULE_PATH})
ENDIF(NOT BUILD_LIBS)

FIND_PACKAGE(Map)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)

INCLUDE_DIRECTORIES(../include)

BUILD_CLIB()
SET(LIBNAME biolib_core-${MAP_VERSION})   # override

ADD_LIBRARY(${LIBNAME} SHARED biolib_error.c)

INSTALL_CLIB()
