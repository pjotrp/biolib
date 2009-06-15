# Module CMake file - builds library in ./contrib

cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_biopp)
SET (M_NAME biopp)
# SET (M_VERSION 1.11.6)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF()

FIND_PACKAGE(Map)

SET(CONTRIB_PATH ${MAP_ROOT}/contrib/biopp)
MESSAGE("CONTRIB_PATH=${GSL_CONTRIB_PATH}")

# SET(LIBNAME ${MAP_projectname}_gsl-${MAP_VERSION})  # shared library name

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)

INCLUDE_DIRECTORIES(.)

BUILD_CLIB()

FILE(STRINGS files.txt CONTRIB_FILES)

ADD_LIBRARY(${LIBNAME} SHARED ${CONTRIB_FILES})

FILE(STRINGS files-nc.txt NC_FILES)
ADD_LIBRARY(numCalcLib SHARED ${NC_FILES})

# ---- The following may be required for OSX
# TARGET_LINK_LIBRARIES(${LIBNAME} ${ZLIB_NAME})

INSTALL_CLIB()
