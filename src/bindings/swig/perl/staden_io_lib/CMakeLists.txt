# Builds the Perl biolib_example library after resolving paths.
#
# Problems:
#
#   cmake PERL_INCLUDE_PATH is hard coded to lib/5.8.8/i686-linux-CORE
#   Builds, but does not install shared library

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME staden_io_lib)
SET (M_VERSION 1.0)
SET (INTERFACE perl_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (CMAKE_MODULE_PATH ../../../../../cmake_modules)
ENDIF(NOT BUILD_LIBS)
# SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

FIND_PACKAGE(BioLibPerl)

ADD_TEST(TestPerlExample ${PERL_EXECUTABLE} -I../${M_NAME} ./../test/test_${M_NAME}.pl)

INSTALL(TARGETS ${M_MODULE}
  LIBRARY DESTINATION ${PERL_SLIB_PATH}
)

INSTALL(FILES ${M_MODULE}.pm DESTINATION ${PERL_LIB_PATH}/biolib )

