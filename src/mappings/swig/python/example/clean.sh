#! /bin/sh
#
# Simple example of building a Python binding - in its simplest form

echo "* clean up build"
rm -vrf CMakeFiles
rm -vf *.cmake
rm -v Makefile
rm -v CMakeCache.txt
rm -v *.cmakerm -v *.o *.c 
rm -v *.so *.py *.pyc
rm -v ../../*.c

