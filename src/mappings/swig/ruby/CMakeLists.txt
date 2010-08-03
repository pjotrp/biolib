if (BLD_BIOLIB_CORE)
  add_subdirectory (biolib_core)
endif()

if (BLD_EXAMPLE)
  add_subdirectory (example)
endif (BLD_EXAMPLE)

if (BLD_AFFYIO)
  add_subdirectory (affyio)
endif (BLD_AFFYIO)

if (BLD_STADEN)
  add_subdirectory (staden_io_lib)
endif (BLD_STADEN)


if (BLD_SAMTOOLS)
  add_subdirectory (samtools)
endif (BLD_SAMTOOLS)


if (BLD_EMBOSS)
  add_subdirectory (emboss)
endif (BLD_EMBOSS)

if (BLD_RQTL)
  add_subdirectory (biolib_R)
  add_subdirectory (rqtl)
endif (BLD_RQTL)
