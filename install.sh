#! /bin/sh
#
# You can pass parameters to CMake. E.g.
#
# to build for Perl:
#
#   ./install.sh
#
# to build one library mapping for Perl:
#
#   ./install.sh --with-staden
#
# to build for Ruby:
#
#   ./install.sh --with-ruby
#
# to build for Python
#
#   ./install.sh --with-python

if [ ! -e PROJECTNAME ]; then
  echo "Only run from BioLib top-level directory"
  exit 1
fi

./configure $*
make
make test
echo "-- No errors? Run 'make install' to complete the installation"
