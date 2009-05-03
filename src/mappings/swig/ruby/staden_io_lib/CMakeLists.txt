# Make biolib_ruby_staden_io_lib module

cmake_minimum_required(VERSION 2.6)
ENABLE_TESTING()

SET (M_NAME staden_io_lib)
SET (M_VERSION 1.11.6)
SET (INTERFACE ruby_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)

SET (USE_ZLIB TRUE)
SET (USE_INCLUDEPATH io_lib)

INCLUDE(CMakeBackwardCompatibilityC)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

FIND_PACKAGE(MapRuby)

ADD_TEST(TestRubyStadenIOLib env PATH=${MODULE_SOURCE_PATH}/io_lib:$PATH ${RUBY_EXECUTABLE} -I../${M_NAME} ./../test/test_${M_NAME}.rb)

INSTALL(TARGETS ${M_MODULE}
  LIBRARY DESTINATION ${RUBY_LIB_PATH}/biolib
)


