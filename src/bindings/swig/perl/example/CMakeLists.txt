# Builds the Perl biolib_example library after resolving paths.
#
# Problems:
#
#   cmake PERL_INCLUDE_PATH is hard coded to lib/5.8.8/i686-linux-CORE
#   Builds, but does not install shared library

cmake_minimum_required(VERSION 2.6)
message("Building Perl library ${SWIG_FLAGS}")
ENABLE_TESTING()

SET (MY_MODULE biolib_perl_example)
SET (INTERFACE perl_example.i)
SET (SOURCES ../../../../clibs/example-1.0/example.c )

FIND_PACKAGE(Perl)
MESSAGE("Using Perl interpreter ${PERL_EXECUTABLE}")
FIND_PACKAGE(PerlLibs)
FIND_PACKAGE(SWIG REQUIRED)

##  INCLUDE_DIRECTORIES(${PERL_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

INCLUDE(${SWIG_USE_FILE})

IF(NOT PERL_INCLUDE_PATH)
  if (PERL_EXECUTABLE)
     EXEC_PROGRAM(${PERL_EXECUTABLE}
			 ARGS -e "'use Config; print \$Config{prefix}, \"\\n\"'"
       OUTPUT_VARIABLE PERL_PREFIX
       RETURN_VALUE PERL_INCLUDE_PATH_RET
       )
     message("PERL prefix=" ${PERL_PREFIX})
		 SET(PERL_POSSIBLE_INCLUDE_PATHS
       "${PERL_PREFIX}/lib/5.8.8/i686-linux/CORE"
     )
		 FIND_PATH(PERL_INCLUDE_PATH perl.h
       ${PERL_POSSIBLE_INCLUDE_PATHS})
  endif (PERL_EXECUTABLE)
  message( "Using PERL include path ${PERL_INCLUDE_PATH}")
ENDIF(NOT PERL_INCLUDE_PATH)

INCLUDE_DIRECTORIES(${PERL_INCLUDE_PATH})

SET(SWIG_FLAGS "")
SET_SOURCE_FILES_PROPERTIES(${INTERFACE} PROPERTIES SWIG_FLAGS "-includeall")

SWIG_ADD_MODULE(${MY_MODULE} perl ${INTERFACE} ${SOURCES} )
# SWIG_LINK_LIBRARIES(${MY_MODULE} ${PERL_LIBRARY} )

ADD_TEST(TestPerlExample ${PERL_EXECUTABLE} ./../test/test_example.pl)

# INSTALL(TARGETS ${MY_MODULE}
#   LIBRARY DESTINATION ${PERL_INCLUDE_PATH}
# )

