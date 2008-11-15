#! /bin/sh

if [ ! -d src ] ; then
  echo Only run from base dir
fi

. ./scripts/cleanup.sh

cmake -DBUILD_RUBY:BOOLEAN=TRUE -DRUBY_EXECUTABLE=/usr/bin/ruby .
make 
make test

cd ./src/bindings/swig/ruby/test
ruby -I../affyio runner.rb
