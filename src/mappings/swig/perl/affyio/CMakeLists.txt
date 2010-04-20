# Builds the Perl biolib_affyio library after resolving paths.
#

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME affyio)
# SET (M_VERSION 1.8)
SET (INTERFACE perl_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)
# SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)
SET(DOXY_XML_FILES "${MAP_ROOT}/build/doc/xml/apidoc/biolib__affyio_8h.xml  ${MAP_ROOT}/build/doc/xml/apidoc/biolib__affyio_8c.xml")

SET (USE_ZLIB TRUE)
SET (USE_RLIB TRUE)

INCLUDE(CMakeBackwardCompatibilityC)

FIND_PACKAGE(MapPerl REQUIRED)

BUILD_PERL_BINDINGS()
TEST_PERL_BINDINGS()
INSTALL_PERL_BINDINGS()

