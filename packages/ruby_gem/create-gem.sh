#!/bin/sh

echo "GEM installation not supported at this point!"
exit 1

if [ ! -d packages ]; then echo "Run gem creator from base directory!" ; exit ; fi

ruby ./packages/ruby_gem/biolib.gemspec


