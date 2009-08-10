# Builds the Perl biolib_libsequence library after resolving paths.

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME libsequence)
SET (M_VERSION 1.6.6)
SET (INTERFACE perl_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)

SET(USE_GSL TRUE)

SET(BOOST_PATH ${MAP_ROOT}/contrib/boost)
SET(GSL_CONTRIB_PATH ${MAP_ROOT}/contrib/gsl)


INCLUDE_DIRECTORIES(${MAP_ROOT}/src/clibs/libsequence-1.6.6/include)
INCLUDE_DIRECTORIES(${MAP_ROOT}/contrib/libsequence-1.6.6)
INCLUDE_DIRECTORIES(/usr/include)
INCLUDE_DIRECTORIES(/usr/local/include)
INCLUDE_DIRECTORIES(${BOOST_PATH})
INCLUDE_DIRECTORIES(${GSL_CONTRIB_PATH})


#SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

FIND_PACKAGE(MapPerl)

POST_BUILD_PERL_BINDINGS()
TEST_PERL_BINDINGS()
INSTALL_PERL_BINDINGS()


