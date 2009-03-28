# Builds the Python biolib_example library after resolving paths.

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME example)
SET (M_VERSION 1.0)
SET (INTERFACE python_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (CMAKE_MODULE_PATH ../../../../../cmake_modules)
ENDIF(NOT BUILD_LIBS)

# SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

FIND_PACKAGE(BioLibPython)

ADD_TEST(TestPythonExample ${PYTHON_EXECUTABLE} ./../test/test_${M_NAME}.py)

# INSTALL(TARGETS ${M_MODULE}
#   LIBRARY DESTINATION ${PERL_SLIB_PATH}
# )

# INSTALL(FILES ${M_MODULE}.pm DESTINATION ${PERL_LIB_PATH}/biolib )

