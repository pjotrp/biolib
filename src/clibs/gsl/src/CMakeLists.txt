# Module CMake file - builds GSL library for ASciLib (A Science Library)

cmake_minimum_required(VERSION 2.6)

PROJECT(ASCILIB_GSL)

IF(NOT BUILD_LIBS)
  # Building in a local module: Set the module search path manually
  SET (CMAKE_MODULE_PATH ../../../../cmake_modules)
  IF(NOT IS_DIRECTORY ${CMAKE_MODULE_PATH})
    MESSAGE(FATAL_ERROR "Can not find ASciLib context")
  ENDIF(NOT IS_DIRECTORY ${CMAKE_MODULE_PATH})
ENDIF(NOT BUILD_LIBS)

FIND_PACKAGE(Map)

SET(GSL_CONTRIB_PATH ${MAP_ROOT}/contrib/gsl)
MESSAGE("GSL_CONTRIB_PATH=${GSL_CONTRIB_PATH}")

SET(LIBNAME ${MAP_projectname}_gsl-${MAP_VERSION})  # shared library name

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(./gsl)

SET(GSL_CONFIG ${GSL_CONTRIB_PATH}/config.h)

IF (NOT EXISTS ${GSL_CONFIG})
  message("Configuring ./contrib/gsl")
  EXECUTE_PROCESS(
    COMMAND /bin/bash -c ./autogen.sh
    COMMAND /bin/bash -c ./configure --enable-maintainer-mode
    WORKING_DIRECTORY ${GSL_CONTRIB_PATH}
    RESULT_VARIABLE result_gsl
  )
  message("Finished configuring ./contrib/gsl ${result_gsl}")
ENDIF (NOT EXISTS ${GSL_CONFIG})

FILE(STRINGS gsl_files.txt GSL_FILES)

ADD_LIBRARY(${LIBNAME} SHARED
  ${GSL_FILES}
)

# ---- The following may be required for OSX
# TARGET_LINK_LIBRARIES(${LIBNAME} ${ZLIB_NAME})

INSTALL(TARGETS ${LIBNAME}
  LIBRARY DESTINATION lib
)

