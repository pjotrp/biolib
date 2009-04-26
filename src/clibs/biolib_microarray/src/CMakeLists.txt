cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_microarray)

IF(NOT BUILD_LIBS)
  SET (CMAKE_MODULE_PATH ../../../../cmake_modules)
ENDIF(NOT BUILD_LIBS)

FIND_PACKAGE(Map REQUIRED)

SET(LIBNAME biolib_microarray-${BIOLIB_VERSION})

INCLUDE_DIRECTORIES(../include)
ADD_LIBRARY(${LIBNAME} SHARED biolib_microarray.c)

INSTALL(TARGETS ${LIBNAME}
  LIBRARY DESTINATION lib
)


