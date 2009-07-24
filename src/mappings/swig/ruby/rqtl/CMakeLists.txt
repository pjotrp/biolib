# Make biolib_ruby_rqtl module

cmake_minimum_required(VERSION 2.6)
ENABLE_TESTING()

SET (M_NAME rqtl)
# SET (M_VERSION 1.12)
SET (INTERFACE ruby_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)

SET (USE_RLIB TRUE)
# SET (USE_ZLIB TRUE)

# INCLUDE(CMakeBackwardCompatibilityC)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)
SET(USE_C_LINKAGE TRUE)

FIND_PACKAGE(MapRuby)

TEST_RUBY_BINDINGS()
INSTALL_RUBY_BINDINGS()

# extra tests
ADD_TEST(TestUnitExtraRuby${M_NAME} ${RUBY_EXECUTABLE} -I../${M_NAME} -I../biolib_core ${MAP_ROOT}/src/extra/ruby/test/runner.rb)


