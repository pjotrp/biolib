# - Find BioLib for PYTHON settings
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

message("Creating Python module ${M_MODULE} (${M_VERSION})")
message("CMAKE_MODULE_PATH=" ${CMAKE_MODULE_PATH})
FIND_PACKAGE(BioLib REQUIRED)
FIND_PACKAGE(PythonLibs REQUIRED)

# ---- Setting the default PYTHON include path
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
# SET (PYTHON_LIB_PATH ${PYTHON_LIBRARY})

FIND_PACKAGE(BioLibModule REQUIRED)
FIND_PACKAGE(BioLibLibraries REQUIRED)

SET (USE_LANGUAGE "Python")
SET (USE_LANGUAGE_LIBRARY ${PYTHON_LIBRARY})
# SET (USE_SWIG_FLAGS ";-prefix;'biolib::'")

FIND_PACKAGE(BioLibSWIG REQUIRED)

MESSAGE( STATUS "PYTHON_LIB_PATH=${PYTHON_LIB_PATH}")

