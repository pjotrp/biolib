#! /bin/sh

swig -ruby example.i
ruby extconf.rb
make
make install
