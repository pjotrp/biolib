if (BLD_EXAMPLE)
  add_subdirectory (example)
endif (BLD_EXAMPLE)

if (BLD_AFFYIO)
  add_subdirectory (affyio)
endif (BLD_AFFYIO)

if (BLD_STADEN)
  add_subdirectory (staden_io_lib)
endif (BLD_STADEN)

# if (BLD_RQTL)
#   add_subdirectory (rqtl)
# endif (BLD_RQTL)

if (BLD_LIBSEQUENCE)
  add_subdirecotry (libsequence)
endif (BLD_LIBSEQUENCE)
