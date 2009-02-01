#! /bin/sh

if [ ! -d cmake_modules ]; then
  echo "Only run from BioLib top-level directory"
  exit 1
fi

sh scripts/cleanup.sh
cmake .
make
make test
echo "Give root password to install libraries - or press Ctrl-C"
su -c "make install"
