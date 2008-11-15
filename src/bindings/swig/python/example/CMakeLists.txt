cmake_minimum_required(VERSION 2.6)
message("Building Python library ${SWIG_FLAGS}")
ENABLE_TESTING()

SET (MY_MODULE biolib_python_example)
SET (INTERFACE python_example.i)
SET (SOURCES ../../../../clibs/example-1.0/example.c )

FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)
FIND_PACKAGE(SWIG REQUIRED)

message( "Using SWIG at ${SWIG_EXECUTABLE}")

IF(NOT PYTHON_LIBRARIES)
  if (PYTHON_EXECUTABLE)
     message( "Using python interpreter at ${PYTHON_EXECUTABLE}")
     EXEC_PROGRAM(${PYTHON_EXECUTABLE}
       ARGS -c "\"import sys; print sys.prefix\""
       OUTPUT_VARIABLE PYTHON_PREFIX
       RETURN_VALUE PYTHON_INCLUDE_PATH_RET
       )
     message("Python prefix=" ${PYTHON_PREFIX})
     EXEC_PROGRAM(${PYTHON_EXECUTABLE}
       ARGS -c "\"import sys; print sys.version[:3]\""
       OUTPUT_VARIABLE PYTHON_VERSION
       RETURN_VALUE PYTHON_INCLUDE_PATH_RET
       )
     message("Python version=" ${PYTHON_VERSION})

  endif (PYTHON_EXECUTABLE)
  message( "Using python path ${PYTHON_PREFIX}")
  SET (PYTHON_INCLUDE_PATH ${PYTHON_PREFIX}/include/python${PYTHON_VERSION})
  SET (PYTHON_LIBRARIES ${PYTHON_PREFIX}/lib/libpython${PYTHON_VERSION}.so)
	message( "Python libraries at ${PYTHON_LIBRARIES}" )
ENDIF(NOT PYTHON_LIBRARIES)

INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

INCLUDE(${SWIG_USE_FILE})

SET(SWIG_FLAGS "")
SET_SOURCE_FILES_PROPERTIES(${INTERFACE} PROPERTIES SWIG_FLAGS "-includeall")

SWIG_ADD_MODULE(${MY_MODULE} python ${INTERFACE} ${SOURCES} )
SWIG_LINK_LIBRARIES(${MY_MODULE} ${PYTHON_LIBRARIES} )

ADD_TEST(TestPythonExample ${PYTHON_EXECUTABLE} ./../test/test_example.py)

# INSTALL(TARGETS ${MY_MODULE}
#   LIBRARY DESTINATION ${PYTHON_INCLUDE_PATH}
# )


