cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_emboss)
SET (M_NAME emboss)

IF(NOT BUILD_LIBS)
  SET (MAP_ROOT ../../../..)
  SET (CMAKE_MODULE_PATH ${MAP_ROOT}/tools/cmake-support/modules)
ENDIF()

FIND_PACKAGE(Map)

SET(CONTRIB_PATH ${MAP_ROOT}/contrib/EMBOSS)

MESSAGE("CONTRIB_PATH=${CONTRIB_PATH}")

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../build)

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(${CONTRIB_PATH}/emboss/function)
INCLUDE_DIRECTORIES(${CONTRIB_PATH}/ajax/core)
INCLUDE_DIRECTORIES(${CONTRIB_PATH}/ajax/pcre)
INCLUDE_DIRECTORIES(${CONTRIB_PATH}/ajax/ajaxdb)
INCLUDE_DIRECTORIES(${CONTRIB_PATH}/ajax/graphics)
INCLUDE_DIRECTORIES(${CONTRIB_PATH}/plplot)

# INCLUDE_DIRECTORIES(${BOOST_PATH})
add_definitions(-DVERSION="6.1" -DLINK_SIZE=4 -DHAVE_MEMMOVE -DPOSIX_MALLOC_THRESHOLD=10)

# Here a hack to get EMBOSS to compile without running configure (may change
# later and run ./configure once)
add_definitions(-DMAX_NAME_COUNT=10000 -DNEWLINE=10 -DMAX_NAME_SIZE=32 -DMATCH_LIMIT=10000000 -DMATCH_LIMIT_RECURSION=MATCH_LIMIT -DBUILD_DIR="${CONTRIB_PATH}/" -DEMBOSS_TOP="${CONTRIB_PATH}/" -DPREFIX="/usr/local")

BUILD_CLIB()

FILE(STRINGS files.txt CONTRIB_FILES)

ADD_LIBRARY(${LIBNAME} SHARED
  ${CONTRIB_FILES}
)

FILE(READ files.txt _list)
STRING(REGEX REPLACE ";" "\\\\;" _list "${_list}")
STRING(REGEX REPLACE "\n" ";" _list "${_list}")

INSTALL_CLIB()

ADD_CUSTOM_TARGET(transform2doxy
  COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation for ${M_NAME}..."
)

include(APIDoc)
foreach(_file ${_list})
  # get_filename_component(target ${_file} NAME_WE)
  get_filename_component(target ${_file} NAME)
  set(_destdir "${MAP_ROOT}/build/transform2doxy/${M_NAME}")
  STRING(CONFIGURE ${_file} _nfile)
  SET(_dfile ${_destdir} / ${target})
  # MESSAGE( ${_dfile} : ${transform2doxy} " -d ${_destdir} ${_nfile}" )
  add_custom_target(${target} 
    COMMENT "Transforming ${_nfile}"
    SOURCES ${_dfile}
    DEPENDS ${_nfile}
    COMMAND ${CMAKE_COMMAND} -E make_directory "${MAP_ROOT}/build/transform2doxy/${M_NAME}"
    COMMAND ${transform2doxy} --quiet -d ${_destdir} ${_nfile}
  )
  add_dependencies(transform2doxy ${target})
endforeach(_file) 

