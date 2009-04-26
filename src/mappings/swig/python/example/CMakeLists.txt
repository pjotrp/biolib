# Builds the Python biolib_example library after resolving paths.

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME example)
SET (M_VERSION 1.0)
SET (INTERFACE python_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (CMAKE_MODULE_PATH ../../../../../cmake_modules)
ENDIF(NOT BUILD_LIBS)

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

FIND_PACKAGE(MapPython REQUIRED)

ADD_CUSTOM_COMMAND(
  TARGET _${M_MODULE}
  POST_BUILD
  COMMAND touch biolib/__init__.py
  COMMAND ${CMAKE_COMMAND} -E copy ${M_NAME}.py biolib/${M_NAME}.py
  COMMAND python -m compileall biolib/
)

ADD_TEST(TestPythonExample ${PYTHON_EXECUTABLE} ./../test/test_${M_NAME}.py)

INSTALL(TARGETS _${M_MODULE}
  LIBRARY DESTINATION ${PYTHON_LIB_PATH}
)

INSTALL(FILES biolib/${M_MODULE}.pyc DESTINATION ${PYTHON_LIB_PATH}/biolib )
INSTALL(FILES biolib/__init__.pyc DESTINATION ${PYTHON_LIB_PATH}/biolib )

