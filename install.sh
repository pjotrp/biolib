#! /bin/sh
#
# You can pass parameters to CMake. E.g.
#
#   ./install.sh -DSTADEN_LIB:BOOLEAN=TRUE -DBUILD_PERL:BOOLEAN=TRUE .
#
# will build the Staden libraries for Perl only...
#

if [ ! -d cmake_modules ]; then
  echo "Only run from BioLib top-level directory"
  exit 1
fi

sh scripts/cleanup.sh
cmake $* .
make
make test
echo "-- Run 'make install' to complete the installation"
