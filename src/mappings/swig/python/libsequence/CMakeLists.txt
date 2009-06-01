# Builds the Python biolib_libsequence library after resolving paths.

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME libsequence)
SET (M_VERSION 1.6.6)
SET (INTERFACE python_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)

SET (USE_INCLUDEPATH ${MAP_ROOT}/contrib/libsequence-1.6.6/Sequence) 
#INCLUDE(CMakeBackwardCompatibilityC)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

#SET(CMAKE_INCLUDE_PATH ${USE_INCLUDEPATH})
#SET(CMAKE_INCLUDE_PATH /usr/include)

FIND_PACKAGE(MapPython REQUIRED)

POST_BUILD_PYTHON_BINDINGS()
TEST_PYTHON_BINDINGS()
INSTALL_PYTHON_BINDINGS()


