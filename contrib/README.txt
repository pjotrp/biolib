In contrib source packages are stored from other sources, which are
used (almost) unmodified by biolib, and which gracefully accept
patches sent upstream. This to allow some stability and, sometimes,
easier deployment.

When code is forked it moves to ~/src/clibs.

For EMBOSS we import the CVS into git with (on Debian you need
git-cvs):

  cd ~/gitcvs
  export CVSROOT=:pserver:cvs@cvs.open-bio.org:/home/repository/emboss
  cvs login # pwd cvs
  git cvsimport -v -d $CVSROOT -C EMBOSS emboss/emboss

Do not change the code in this tree - it is a copy. 

Note: this is up for reconsideration. Could well be we end up using
tarballs, as EMBOSS faithfully keeps all versions.
