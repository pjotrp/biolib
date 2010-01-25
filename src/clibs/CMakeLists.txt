cmake_minimum_required(VERSION 2.6)

if(BLD_BIOLIB_CORE)
  add_subdirectory (biolib_core/src)
endif()

if(BLD_BIOLIB_R)
  add_subdirectory (biolib_R/src)
endif()

if(BLD_EXAMPLE)
  add_subdirectory (example-1.0)
endif()

if (BLD_AFFYIO)
  add_subdirectory (affyio-1.8/src)
  add_subdirectory (biolib_microarray/src)
endif()

if (BLD_STADEN)
  add_subdirectory (staden_io_lib/src)
endif()

if (BLD_EMBOSS)
  add_subdirectory (emboss/src)
endif (BLD_EMBOSS)

if (BLD_RQTL)
  add_subdirectory (rqtl/contrib/biolib)
endif (BLD_RQTL)

if (BLD_LIBSEQUENCE)
  add_subdirectory (libsequence-1.6.6/src)
endif (BLD_LIBSEQUENCE)
