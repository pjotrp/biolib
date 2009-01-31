# Make biolib_ruby_staden-io_lib module

cmake_minimum_required(VERSION 2.6)
ENABLE_TESTING()

SET (M_NAME staden_io_lib)
SET (M_VERSION 1.11.6)
SET (INTERFACE ruby_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (CMAKE_MODULE_PATH ../../../../../cmake_modules)
ENDIF(NOT BUILD_LIBS)

SET (USE_ZLIB TRUE)
SET (USE_INCLUDE io_lib)

INCLUDE(CMakeBackwardCompatibilityC)

FIND_PACKAGE(BioLibRuby)

# ADD_TEST(TestRubyAffyio ${RUBY_EXECUTABLE} -I../${M_NAME} ./../test/test_${M_NAME}.rb)

INSTALL(TARGETS ${M_MODULE}
  LIBRARY DESTINATION ${RUBY_LIB_PATH}/biolib
)


