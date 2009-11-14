# Builds the Perl biolib_example library after resolving paths.
#
# Problems:
#
#   cmake PERL_INCLUDE_PATH is hard coded to lib/5.8.8/i686-linux-CORE
#   Builds, but does not install shared library

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME staden_io_lib)
SET (M_VERSION 1.11.6)
SET (INTERFACE perl_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)
# SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

SET (USE_ZLIB TRUE)
SET (USE_INCLUDEPATH io_lib)

INCLUDE(CMakeBackwardCompatibilityC)

FIND_PACKAGE(MapPerl)

POST_BUILD_PERL_BINDINGS()
TEST_PERL_BINDINGS()
INSTALL_PERL_BINDINGS()

