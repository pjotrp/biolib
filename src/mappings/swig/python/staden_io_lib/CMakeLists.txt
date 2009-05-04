# Builds the Python biolib_staden_io_lib library after resolving paths.

cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME staden_io_lib)
SET (M_VERSION 1.11.6)
SET (INTERFACE python_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)

SET (USE_ZLIB TRUE)
SET (USE_INCLUDEPATH io_lib)

INCLUDE(CMakeBackwardCompatibilityC)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

FIND_PACKAGE(MapPython REQUIRED)

ADD_CUSTOM_COMMAND(
  TARGET _${M_MODULE}
  POST_BUILD
  COMMAND touch biolib/__init__.py
  COMMAND ${CMAKE_COMMAND} -E copy ${M_NAME}.py biolib/${M_NAME}.py
  COMMAND python -m compileall biolib/
)

ADD_TEST(TestPythonStadenIOLib env PATH=${MODULE_SOURCE_PATH}/io_lib:$PATH ${PYTHON_EXECUTABLE} ./../test/test_${M_NAME}.py)

INSTALL(TARGETS _${M_MODULE}
  LIBRARY DESTINATION ${PYTHON_LIB_PATH}
)

INSTALL(FILES biolib/${M_MODULE}.pyc DESTINATION ${PYTHON_LIB_PATH}/biolib )
INSTALL(FILES biolib/__init__.pyc DESTINATION ${PYTHON_LIB_PATH}/biolib )

