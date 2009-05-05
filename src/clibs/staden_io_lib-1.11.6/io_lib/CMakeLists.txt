cmake_minimum_required(VERSION 2.6)

PROJECT(Biolib_staden_iolib)
SET (M_NAME staden_io_lib)
SET (M_VERSION 1.11.6)

IF(NOT BUILD_LIBS)
  SET (CMAKE_MODULE_PATH ../../../../cmake_modules)
ENDIF(NOT BUILD_LIBS)

FIND_PACKAGE(Map REQUIRED)
FIND_PACKAGE(ZLIB REQUIRED)

INCLUDE_DIRECTORIES(.)
INCLUDE_DIRECTORIES(..)
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_PATH})

BUILD_CLIB()

ADD_LIBRARY(${LIBNAME} SHARED
array.c
compress.c
compression.c
ctfCompress.c
deflate_interlaced.c
error.c
expFileIO.c
files.c
find.c
fpoint.c
hash_table.c
jenkins_lookup3.c
mach-io.c
mFILE.c
misc_scf.c
open_trace_file.c
read_alloc.c
Read.c
read_scf.c
scf_extras.c
seqIOABI.c
seqIOALF.c
seqIOCTF.c
seqIOPlain.c
sff.c
srf.c
strings.c
traceType.c
translate.c
vlen.c
write_scf.c
xalloc.c
ztr.c
ztr_translate.c
)

# ---- The following may be required for OSX
TARGET_LINK_LIBRARIES(${LIBNAME} ${ZLIB_NAME})

INSTALL_CLIB()
