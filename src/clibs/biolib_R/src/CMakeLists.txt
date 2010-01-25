cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_R)
SET (M_NAME biolib_R)

IF(NOT BUILD_LIBS)
  # Building in a local module: Set the module search path manually
  SET (MAP_ROOT ../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
  IF(NOT IS_DIRECTORY ${CMAKE_MODULE_PATH})
    MESSAGE(FATAL_ERROR "Can not find BioLib context")
  ENDIF(NOT IS_DIRECTORY ${CMAKE_MODULE_PATH})
ENDIF(NOT BUILD_LIBS)

SET(USE_CORE TRUE)
SET(USE_RLIB TRUE)

FIND_PACKAGE(Map)
FIND_PACKAGE(MapLibraries)
FIND_PACKAGE(Rlibs)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)

INCLUDE_DIRECTORIES(../include)
INCLUDE_DIRECTORIES(../../biolib_core/include)

SET(LIBNAME biolib_R-${MAP_VERSION})   # override
ADD_LIBRARY(${LIBNAME} SHARED biolib_R_map.c)

BUILD_CLIB()

INSTALL_CLIB()


