#! /bin/sh
#
# You can pass parameters to CMake. E.g.
#
#   sh install.sh -DSTADEN_LIB:BOOLEAN=TRUE -DBUILD_PERL:BOOLEAN=TRUE .

if [ ! -d cmake_modules ]; then
  echo "Only run from BioLib top-level directory"
  exit 1
fi

sh scripts/cleanup.sh
cmake $* .
make
make test
echo "Give root password to install libraries - or press Ctrl-C"
su -c "make install"
