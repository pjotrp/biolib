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

SET(BOOST_PATH ${MAP_ROOT}/contrib/boost)

INCLUDE_DIRECTORIES(${MAP_ROOT}/src/clibs/libsequence-1.6.6/include)
INCLUDE_DIRECTORIES(${MAP_ROOT}/contrib/libsequence-1.6.6)
INCLUDE_DIRECTORIES(/usr/include)
INCLUDE_DIRECTORIES(/usr/local/include)
INCLUDE_DIRECTORIES(${BOOST_PATH})

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

FIND_PACKAGE(MapPython REQUIRED)

POST_BUILD_PYTHON_BINDINGS()
TEST_PYTHON_BINDINGS()
INSTALL_PYTHON_BINDINGS()


