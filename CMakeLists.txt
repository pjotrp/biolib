# CMakeLists.txt root folder for BIOLIB (see http://biolib.open-bio.org/)
#
# Build everything:
#
#   cmake .
#
# Conditionals:
#
#   Build the libraries without language interfaces:
#
#   cmake -DBUILD_LIBS:BOOLEAN=TRUE .
#   cmake -DBUILD_DOCS:BOOLEAN=TRUE .
#
#   Build the Ruby/Python/Perl interface and libraries:
#
#   cmake -DBUILD_RUBY:BOOLEAN=TRUE .
#   cmake -DBUILD_PYTHON:BOOLEAN=TRUE .
#   cmake -DBUILD_PERL:BOOLEAN=TRUE .
#
#   each of these will include BUILD_LIBS
#
#   To build specific libraries, for example
#
#   cmake -DSTADEN_LIB:BOOLEAN=TRUE
#   cmake -DRQTL_LIB:BOOLEAN=TRUE
#
#   Combine with BUILD_RUBY (etc.) to build just one library type.
#
# See ./INSTALL for more information

cmake_minimum_required(VERSION 2.6)

project (BIOLIB)

# Testing: 
#
#   test:             Run fast 'integration' tests
#   testunit:         Run unit testing
#   testdoc:          Run doctest testing
#   testregression:   Run all regression tests
#   testall:          Run all tests
#
ENABLE_TESTING()
ADD_CUSTOM_TARGET(testregression ALL COMMAND ctest -R TestRegression)
ADD_CUSTOM_TARGET(testunit ALL COMMAND ctest -R TestUnit)
ADD_CUSTOM_TARGET(testdoc ALL COMMAND ctest -R TestDoc)
ADD_CUSTOM_TARGET(testall ALL COMMAND ctest)
ADD_CUSTOM_TARGET(test ALL COMMAND ctest -E "TestRegression\\|Slow\\|TestDoc")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/tools/cmake-support/modules/")
message("CMake modules: ${CMAKE_MODULE_PATH}")

FIND_PACKAGE(GitSubmodule)

include(CheckIncludeFiles)

message("Building biolib:")

if(BUILD_ALL)
	set(BUILD_RUBY TRUE)
	set(BUILD_PERL TRUE)
	set(BUILD_PYTHON TRUE)
endif(BUILD_ALL)

if(BUILD_RUBY)
  message("  Ruby interface")
	set(BUILD_LIBS TRUE)
endif(BUILD_RUBY)

if(BUILD_PYTHON)
  message("  Python interface")
	set(BUILD_LIBS TRUE)
endif(BUILD_PYTHON)

if(BUILD_PERL)
  message("  Perl interface")
	set(BUILD_LIBS TRUE)
endif(BUILD_PERL)

if(NOT BUILD_DOCS)
  if(NOT BUILD_LIBS)
    set(BUILD_LIBS TRUE)
	  message("  Building libraries only")
    set(BUILD_RUBY TRUE)
    message("  Ruby interface")
    # set(BUILD_PYTHON TRUE)
    # set(BUILD_PERL TRUE)
  endif(NOT BUILD_LIBS)
endif(NOT BUILD_DOCS)

set(BLD_BIOLIB_CORE  TRUE)
set(BLD_STADEN  TRUE)
set(BLD_RQTL    FALSE) 
set(BLD_EXAMPLE TRUE)
IF(NOT CYGWIN AND NOT APPLE)
  set(BLD_AFFYIO  TRUE)
ENDIF(NOT CYGWIN AND NOT APPLE)

if (EXAMPLE_LIB)
  set(BLD_STADEN  FALSE)
  set(BLD_RQTL    FALSE)
  set(BLD_AFFYIO  FALSE)
  set(BLD_EXAMPLE TRUE)
  set(BLD_BIOLIB_CORE  FALSE)
endif (EXAMPLE_LIB)

if (AFFYIO_LIB)
  set(BLD_STADEN  FALSE)
  set(BLD_RQTL    FALSE)
  set(BLD_AFFYIO  TRUE)
  set(BLD_EXAMPLE FALSE)
  set(BLD_BIOLIB_CORE  TRUE)   # requires biolib error handler
endif (AFFYIO_LIB)

if (STADEN_LIB)
  set(BLD_STADEN  TRUE)
  set(BLD_RQTL    FALSE)
  set(BLD_AFFYIO  FALSE)
  set(BLD_EXAMPLE FALSE)
  set(BLD_BIOLIB_CORE  FALSE)
endif (STADEN_LIB)

if (RQTL_LIB)
  set(BLD_RQTL    TRUE)
  set(BLD_BIOLIB_CORE  TRUE)
  set(BLD_BIOLIB_R     TRUE)
  set(BLD_STADEN  FALSE)
  set(BLD_AFFYIO  FALSE)
  set(BLD_EXAMPLE TRUE)        # contains typemap tests
endif (RQTL_LIB)

if (EXAMPLE_LIB)
  set(BLD_RQTL    FALSE)
  set(BLD_STADEN  FALSE)
  set(BLD_AFFYIO  FALSE)
  set(BLD_EXAMPLE TRUE)
  set(BLD_BIOLIB_CORE  FALSE)
endif (EXAMPLE_LIB)

message("  Biolib libraries")
message(STATUS "Install Affyio ${BLD_AFFYIO}")
message(STATUS "Install Staden ${BLD_STADEN}")
message(STATUS "Install RQTL ${BLD_RQTL}")
message(STATUS "Install Example ${BLD_EXAMPLE}")

FIND_PACKAGE(Map)

# SET(CMAKE_BUILD_TYPE Debug)  Release is on by default
if(DEBUG)
  SET(CMAKE_BUILD_TYPE Debug)
else(DEBUG)
  SET(CMAKE_BUILD_TYPE Release)
endif(DEBUG)
SET(DEFAULT_BUILD_SHARED_LIBS ON)
SET(BUILD_SHARED_LIBS ${DEFAULT_BUILD_SHARED_LIBS} CACHE BOOL "Building shared or static libraries")

# Documentation
if (BUILD_DOCS)
  INCLUDE (APIDoc)
endif (BUILD_DOCS)

# Turn off chatty makefiles by default.  To make them chatty again,
# call make with VERBOSE=1 like this:
#
# make VERBOSE=1

SET(CMAKE_VERBOSE_MAKEFILE OFF)

############################################################
# Set default search directory prefixes for third party libraries.

SET(THIRD_PARTY_LIBRARY_PATH "" CACHE PATH "Default search path for third-party libraries")
SET(THIRD_PARTY_INCLUDE_PATH "" CACHE PATH "Default search path for third-party headers")

add_subdirectory (src)
include(src)

FIND_PACKAGE(SystemInfo)
