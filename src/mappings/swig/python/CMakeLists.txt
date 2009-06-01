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

POST_BUILD_PYTHON_BINDINGS()
TEST_PYTHON_BINDINGS()
INSTALL_PYTHON_BINDINGS()

