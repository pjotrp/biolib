#! /bin/sh
#
# Simple example of building a Perl binding - in its simplest form

library=biolib_perl_example

echo "* SWIG"
swig -perl5 -o ${library}_wrap.c perl_example.i 

echo "* gcc"
gcc -c ../../../../clibs/example-1.0/example.c ${library}_wrap.c `perl -MExtUtils::Embed -e ccopts`

echo "* ld"
ld -shared example.o ${library}_wrap.o -o ${library}.so 

echo "* clean up build"
rm -v *.o *.c 

echo "* test"
perl -I`pwd` ../test/test_example.pl

echo "* clean up runtime"
rm -v *.so *.pm


