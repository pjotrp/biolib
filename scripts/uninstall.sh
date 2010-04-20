#! /bin/bash
#
# Remove installed libraries (run with right permissions)

if [ ! -e install_manifest.txt ]; then
  echo "FATAL: Can not find ./install_manifest.txt"
  exit 1
fi

for x in `cat install_manifest.txt` ; do rm -v $x ; done
# xargs rm -v < install_manifest.txt

