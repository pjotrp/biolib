#! /bin/sh

if [ -d /nix/var/nix/profiles/Debian ]; then
  echo Use clean Debian profile for testing
  nix-env --switch-profile /nix/var/nix/profiles/Debian
fi
sh scripts/cleanup.sh
# rake -f packages/source_pkg/Rakefile 
# rake -f packages/source_pkg/Rakefile test
rake -f packages/source_pkg/Rakefile package
