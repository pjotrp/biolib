#! /bin/sh

if [ ! -d src ] ; then
  echo Only run from base dir
fi

. ./scripts/cleanup.sh

cmake -DBUILD_LIBS:BOOLEAN=TRUE .
make 
make test
