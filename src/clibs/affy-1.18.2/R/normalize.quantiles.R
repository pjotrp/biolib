##################################################################
##
## file: normalize.quantiles.R
##
## For a description of quantile normalization method see
##
##  Bolstad, B. M., Irizarry R. A., Astrand, M, and Speed, T. P. (2003)(2003)
##  A Comparison of Normalization Methods for High
##  Density Oligonucleotide Array Data Based on Bias and Variance.
##  Bioinformatics 19,2,pp 185-193
##
## History
## Pre Aug 23, 2003 Two years worth of stuff
## Aug 23, 2003 - Added use.log2 to "robust",
##                added ability to pass additional parameters
##                to normalize.AffyBatch.Quantiles.robust
##                changed pmonly parameters on functions
##                so that it is now a string argument "type"
##                the options are pmonly, mmonly, together, separate
## Jan 31, 2004 - put a check for an integer matrix and force coercision to
##                doubles if required in normalize.quantiles
## Mar 13, 2005 - Modifications to normalize.quantiles.robust including removing
##                approx.method which never got implemented. Making it a use a .Call()
##                rather than a .C()
##
## Sep 20, 2006 - fix .Call in normalize.quantiles.robust
## May 20, 2007 - remove the functions that have been moved to preprocessCore
##
##################################################################

normalize.AffyBatch.quantiles <- function(abatch,type=c("separate","pmonly","mmonly","together")) {


  type <- match.arg(type)

  if ((type == "pmonly")|(type == "separate")){
    pms <- unlist(pmindex(abatch))
    ## Change to faster computation of noNA - SDR 11/06/2003
    ##noNA <- apply(intensity(abatch)[pms,,drop=FALSE],1,function(x) all(!is.na(x)))
    noNA <- rowSums(is.na(intensity(abatch)[pms,,drop=FALSE])) == 0
    pms <- pms[noNA]
    intensity(abatch)[pms,] <- normalize.quantiles(intensity(abatch)[pms,,drop=FALSE ],copy=FALSE)
  }
  if((type == "mmonly") | (type == "separate")){
    mms <- unlist(mmindex(abatch))
    ## Change to faster computation of noNA - SDR 11/06/2003
    ##noNA <- apply(intensity(abatch)[mms,,drop=FALSE],1,function(x) all(!is.na(x)))
    noNA <- rowSums(is.na(intensity(abatch)[mms,,drop=FALSE])) == 0
    mms <- mms[noNA]

    intensity(abatch)[mms,] <- normalize.quantiles(intensity(abatch)[mms,,drop=FALSE ],copy=FALSE)
  }
  if (type == "together"){
    pms <- unlist(indexProbes(abatch,"both"))
    intensity(abatch)[pms,]  <- normalize.quantiles(intensity(abatch)[pms,,drop=FALSE ],copy=FALSE)
  }

  ##this is MIAME we need to decide how to do this properly.
  ##for (i in 1:length(abatch)) {
  ##  history(abatch)[[i]]$name <- "normalized by quantiles"
  ##}

  return(abatch)
}

normalize.AffyBatch.quantiles.robust <- function(abatch, type=c("separate","pmonly","mmonly","together"),weights=NULL,remove.extreme=c("variance","mean","both","none"),n.remove=1,use.median=FALSE,use.log2=FALSE) {

  type <- match.arg(type)

  if ((type == "pmonly")|(type == "separate")){
    pms <- unlist(pmindex(abatch))
    intensity(abatch)[pms, ] <- normalize.quantiles.robust(intensity(abatch)[pms, ], copy=FALSE,weights=weights,remove.extreme,n.remove=n.remove,use.median=use.median,use.log2=use.log2)
  }
  if ((type == "mmonly")|(type == "separate")){
    mms <- unlist(mmindex(abatch))
    intensity(abatch)[mms, ] <- normalize.quantiles.robust(intensity(abatch)[mms, ],copy=FALSE,weights=weights,remove.extreme,n.remove=n.remove,use.median=use.median,use.log2=use.log2)
  }

  if (type == "together"){
    pms <- unlist(indexProbes(abatch,"both"))
    intensity(abatch)  <- normalize.quantiles.robust(intensity(abatch)[pms,,drop=FALSE ],copy=FALSE, weights=weights,remove.extreme=remove.extreme,n.remove=n.remove,use.median=use.median,use.log2=use.log2)
  }



  ##this is MIAME we need to decide how to do this properly.
  ##for (i in 1:length(abatch)) {
  ##  history(abatch)[[i]]$name <- "normalized by quantiles"
  ##}

  return(abatch)
}

