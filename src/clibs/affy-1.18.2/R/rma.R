######################################################
#
# rma - RMA interface to c code
#
# the RMA method implemented in c code
#
# this code serves as interface to the c code.
# currently
# implemented (version 0.25) background correction
#
# Background correction code has been added.
#
# note this function does not leave the supplied
# AffyBatch unchanged if you select DESTRUCTIVE=TRUE. this is
# for memory purposes but can be quite
# dangerous if you are not careful. Use destructive=FALSE if this is
# deemed likely to be a problem.
#
# UPDATE: note that the affybatch is now not affected if you use
# destructive=TRUE and you might actually save a little memory.
# the destructive refers only to Plobs, which would be destroyed.
#
# History
#
# Feb 22, 2004 - activated subset. In is now possible to
#                do the entire RMA procedure using a subset of probesets
#
# Oct 26, 2007 = makesure verbosity flag is correctly passed down to C-level routines
#
# OCt 28, 2007 MM are no longer passed to the C code
#
#
########################################################

rma <- function(object,subset=NULL, verbose=TRUE, destructive = TRUE,normalize=TRUE,background=TRUE,bgversion=2,...){

  rows <- length(probeNames(object,subset))
  cols <- length(object)

  if (is.null(subset)){
    ngenes <- length(geneNames(object))
  } else {
    ngenes <- length(subset)
  }

  #background correction
  bg.dens <- function(x){density(x,kernel="epanechnikov",n=2^14)}

  if (destructive){
  	exprs <-
  	.Call("rma_c_complete",pm(object,subset), probeNames(object,subset),ngenes,body(bg.dens),new.env(),normalize,background,bgversion, verbose,
  	PACKAGE="affy")
  } else {
	exprs <-
  	.Call("rma_c_complete_copy", pm(object,subset), probeNames(object,subset), ngenes,
  	body(bg.dens), new.env(), normalize, background, bgversion, verbose,
  	PACKAGE="affy")
  }
  colnames(exprs) <- sampleNames(object)

  new("ExpressionSet",
      phenoData = phenoData(object),
      annotation = annotation(object),
      experimentData = experimentData(object),
      exprs = exprs)
}
