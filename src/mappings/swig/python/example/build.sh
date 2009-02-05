#! /bin/sh
#
# Simple example of building a Python binding - in its simplest form

library=biolib_python_example

echo "* SWIG"
swig -python -o ${library}_wrap.c python_example.i 

echo "* gcc"
gcc -c ../../../../clibs/example-1.0/example.c ${library}_wrap.c -I/usr/include/python2.4

echo "* ld"
ld -shared example.o ${library}_wrap.o -o _${library}.so 

echo "* clean up build"
rm -v *.o *.c 

echo "* test"
env PYTHONPATH=`pwd` python ../test/test_example.py

echo "* clean up runtime"
rm -v *.so *.py *.pyc


