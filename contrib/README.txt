In contrib source packages are stored from other sources, which are
used (almost) unmodified by biolib, and which gracefully accept
patches sent upstream. This to allow some stability and, sometimes,
easier deployment.

When code is forked, and contains many changes, it moves to
~/src/clibs.

For EMBOSS we import/update the CVS into git with (on Debian you need
git-cvs):

  cd ~/gitcvs
  export CVSROOT=:pserver:cvs@cvs.open-bio.org:/home/repository/emboss
  cvs login # pwd cvs
  git cvsimport -v -d $CVSROOT -C EMBOSS emboss/emboss

or if you have a special branch (which you should have on update, to
make sure everything works):

  git cvsimport -o branch -v -d $CVSROOT -C EMBOSS emboss/emboss

After updating from CVS avoid changing the code a ./contrib tree - it
is a copy.

Note: this is up for reconsideration. Could well be we end up using
tarballs, as EMBOSS faithfully keeps all versions online.

For Bio++ a similar checkout is done:

  export CVSROOT=:pserver:anoncvs@kimura.univ-montp2.fr:/usr/local/cvsroot ; cvs login ; git cvsimport -v -d $CVSROOT -C numcalc numcalc


