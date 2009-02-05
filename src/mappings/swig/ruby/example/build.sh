#! /bin/sh
#
# Simple example of building a Ruby binding - in its simplest form

library=biolib_ruby_example
wrap=${library}_wrap
includes=`ruby -e "require 'rbconfig' ; puts Config::CONFIG['topdir']  "`

echo "* SWIG"
swig -ruby -o ${library}_wrap.c ruby_example.i 

echo "* gcc"
gcc -c ../../../../clibs/example-1.0/example.c $wrap.c -I$includes

echo "* ld"
ld -shared example.o $wrap.o -o $library.so 

echo "* clean up build"
rm -v *.o *.c

echo "* test"
ruby -I`pwd` ../test/test_example.rb

echo "* clean up runtime"
rm -v *.so 

