cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()

SET (M_NAME biopp)
# SET (M_VERSION 1.11.6)
SET (INTERFACE python_${M_NAME}.i)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF(NOT BUILD_LIBS)

# SET (USE_ZLIB TRUE)

INCLUDE_DIRECTORIES("${MAP_ROOT}/contrib/biopp/utils/Utils")
SET (USE_SWIG_INCLUDEPATH "${MAP_ROOT}/contrib/biopp/utils/Utils;-I/usr/include/c++/4.3;-I/usr/include/c++/4.3/i486-linux-gnu;-I/usr/include;-I/usr/include/linux")
SET (USE_INCLUDEPATH utils/Utils)

SET(USE_SWIG_INCLUDEALL TRUE)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY biolib)

FIND_PACKAGE(MapPython REQUIRED)

POST_BUILD_PYTHON_BINDINGS()
TEST_PYTHON_BINDINGS()
INSTALL_PYTHON_BINDINGS()

