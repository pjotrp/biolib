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
  SET (CMAKE_MODULE_PATH ../../../../../cmake_modules)
ENDIF(NOT BUILD_LIBS)
# SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

SET (USE_ZLIB TRUE)
SET (USE_INCLUDEPATH io_lib)

INCLUDE(CMakeBackwardCompatibilityC)

FIND_PACKAGE(BioLibPerl REQUIRED)

ADD_CUSTOM_COMMAND(
  TARGET ${M_MODULE}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${M_NAME}.pm biolib/${M_NAME}.pm
)
IF(APPLE)
  ADD_CUSTOM_COMMAND(
    TARGET ${M_MODULE}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${M_NAME}.so ${M_NAME}.dylib
  )
ENDIF(APPLE)


ADD_TEST(TestPerlStadenIOLib ${PERL_EXECUTABLE} -I../${M_NAME}/biolib ./../test/test_${M_NAME}.pl)

INSTALL(TARGETS ${M_MODULE}
  LIBRARY DESTINATION ${PERL_SLIB_PATH}
)

INSTALL(FILES ${M_MODULE}.pm DESTINATION ${PERL_LIB_PATH}/biolib )

