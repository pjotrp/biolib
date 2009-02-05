# Make biolib_ruby_example.so

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME example)
SET (M_VERSION 1.0)
SET (INTERFACE ruby_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (CMAKE_MODULE_PATH ../../../../../cmake_modules)
ENDIF(NOT BUILD_LIBS)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

FIND_PACKAGE(BioLibRuby)

ADD_TEST(TestRubyExample ${RUBY_EXECUTABLE} -I../${M_NAME} ./../test/test_${M_NAME}.rb)

INSTALL(TARGETS ${M_MODULE}
  LIBRARY DESTINATION ${RUBY_LIB_PATH}/biolib
)

