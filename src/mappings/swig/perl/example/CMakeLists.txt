# Builds the Perl biolib_example library after resolving paths.
#

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME example)
SET (M_VERSION 1.0)
SET (INTERFACE perl_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)
# SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

INCLUDE(CMakeBackwardCompatibilityC)

FIND_PACKAGE(MapPerl)

POST_BUILD_PERL_BINDINGS()
TEST_PERL_BINDINGS()
INSTALL_PERL_BINDINGS()

