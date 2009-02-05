#! /bin/sh
#
# You can pass parameters to CMake. E.g.
#
# to build for Perl:
#
#   ./install.sh -DBUILD_PERL:BOOLEAN=TRUE .
#
# to build one library mapping for Perl:
#
#   ./install.sh -DSTADEN_LIB:BOOLEAN=TRUE -DBUILD_PERL:BOOLEAN=TRUE .
#

if [ ! -d cmake_modules ]; then
  echo "Only run from BioLib top-level directory"
  exit 1
fi

sh scripts/cleanup.sh
cmake $* .
make
make test
echo "-- No errors? Run 'make install' to complete the installation"
