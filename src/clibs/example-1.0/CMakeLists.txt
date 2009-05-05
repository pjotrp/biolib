cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_example)
IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)

FIND_PACKAGE(Map REQUIRED)

SET(LIBNAME biolib_example-${MAP_VERSION})
BUILD_CLIB(./build)

INCLUDE_DIRECTORIES(.)

ADD_LIBRARY(${LIBNAME} SHARED example.c)

INSTALL_CLIB()

