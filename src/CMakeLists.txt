cmake_minimum_required(VERSION 2.6)

if (BUILD_LIBS)
  add_subdirectory (clibs)
endif (BUILD_LIBS)

if (BUILD_RUBY)
  add_subdirectory (mapings/swig/ruby)
endif(BUILD_RUBY)
if (BUILD_PYTHON)
  add_subdirectory (mapings/swig/python)
endif(BUILD_PYTHON)
if (BUILD_PERL)
  add_subdirectory (mapings/swig/perl)
endif(BUILD_PERL)

