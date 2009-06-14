cmake_minimum_required(VERSION 2.6)

if(BLD_BIOLIB)
  add_subdirectory (biolib_core/src)
endif()

if(BLD_EXAMPLE)
  add_subdirectory (example-1.0)
endif()

if (BLD_AFFYIO)
  add_subdirectory (affyio-1.8/src)
  add_subdirectory (biolib_microarray/src)
endif()

if (BLD_STADEN)
  add_subdirectory (staden_io_lib-1.11.6/io_lib)
endif()

if (BLD_RQTL)
  add_subdirectory (biolib_R/src)
  add_subdirectory (rqtl/contrib/biolib)
endif()
