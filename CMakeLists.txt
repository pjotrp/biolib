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
#   cmake -DBUILD_LIBS:BOOLEAN=ON .
#   cmake -DBUILD_DOCS:BOOLEAN=ON .
#
#   Build the Ruby/Python/Perl interface and libraries:
#
#   cmake -DBUILD_RUBY:BOOLEAN=ON .
#   cmake -DBUILD_PYTHON:BOOLEAN=ON .
#   cmake -DBUILD_PERL:BOOLEAN=ON .

cmake_minimum_required(VERSION 2.6)

project (BIOLIB)

ENABLE_TESTING()
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
message("CMake modules: ${CMAKE_MODULE_PATH}")
include(CheckIncludeFiles)

message("Building biolib:")

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

message("  Biolib libraries")
FIND_PACKAGE(BioLib)

# SET(CMAKE_BUILD_TYPE Debug)
SET(DEFAULT_BUILD_SHARED_LIBS ON)
SET(BUILD_SHARED_LIBS ${DEFAULT_BUILD_SHARED_LIBS} CACHE BOOL "Building shared or static libraries")

# Documentation
if (BUILD_DOCS)
INCLUDE (cmake_modules/APIDoc.cmake)
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


