# - Find BioLib for Ruby settings
#
# Expects M_NAME, M_VERSION to be set!
#
# Special parameters are:
#
#   USE_INCLUDEPATH - find module include files here
#   USE_SWIG_INCLUDEALL - tell SWIG to parse all include files for 
#     info (not recommended as all C headers are pulled in too)
#   USE_RLIB - link the R libraries
#   USE_ZLIB - link Zlib
#   USE_BIOLIBCORE - link the core lib

SET (M_MODULE ${M_NAME})

message("Creating Ruby module ${M_MODULE} (${M_VERSION})")
FIND_PACKAGE(BioLib)
FIND_PACKAGE(Ruby)

# ---- Setting the default Ruby include path
INCLUDE_DIRECTORIES(${RUBY_INCLUDE_PATH})
SET (RUBY_LIB_PATH ${RUBY_INCLUDE_PATH})

FIND_PACKAGE(BioLibModule)
FIND_PACKAGE(BioLibLibraries)

SET (USE_LANGUAGE "ruby")
SET (USE_LANGUAGE_LIBRARY ${RUBY_LIBRARY})

FIND_PACKAGE(BioLibSWIG)

IF(USE_RLIB)
  # handle the QUIETLY and REQUIRED arguments and set RLIBS_FOUND to TRUE if 
  # all listed variables are TRUE
  INCLUDE(FindPackageHandleStandardArgs)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(RLibs DEFAULT_MSG BIOLIB_RUBY_VERSION)
ENDIF(USE_RLIB)

MESSAGE("BIOLIB_RUBY_VERSION=${BIOLIB_VERSION}")
MESSAGE("RUBY_LIB_PATH=${RUBY_LIB_PATH}")
# this is used when searching for include files e.g. using the FIND_PATH() command.
MESSAGE( STATUS "CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH} )
# this is used when searching for libraries e.g. using the FIND_LIBRARY() command.
MESSAGE( STATUS "CMAKE_LIBRARY_PATH: " ${CMAKE_LIBRARY_PATH} )

MARK_AS_ADVANCED(
  BIOLIB_RUBY_VERSION
  )



