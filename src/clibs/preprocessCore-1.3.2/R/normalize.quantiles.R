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
## May 20, 2007 - port to preprocessCore. Remove anything to do with AffyBatch Objects
##
##################################################################

normalize.quantiles <- function(x,copy=TRUE){

  rows <- dim(x)[1]
  cols <- dim(x)[2]

  if (!is.matrix(x)){
    stop("Matrix expected in normalize.quantiles")
  }

  if (is.integer(x)){
    x <- matrix(as.double(x),rows,cols)
    copy <- FALSE
  }

  #matrix(.C("qnorm_c", as.double(as.vector(x)), as.integer(rows), as.integer(cols))[[1]], rows, cols)

##  .Call("R_qnorm_c",x,copy, PACKAGE="preprocessCore");
  .Call("R_qnorm_c_handleNA",x,copy, PACKAGE="preprocessCore");
}


normalize.quantiles.robust <- function(x,copy=TRUE,weights=NULL,remove.extreme=c("variance","mean","both","none"),n.remove=1,use.median=FALSE,use.log2=FALSE){

  calc.var.ratios <- function(x){
    cols <- dim(x)[2]
    vars <- apply(x,2,var)
    results <- matrix(0,cols,cols)
    for (i in 1:cols-1)
      for (j in (i+1):cols){
        results[i,j] <- vars[i]/vars[j]
        results[j,i] <- vars[j]/vars[i]
      }
    results
  }

  calc.mean.dists <- function(x){
    cols <- dim(x)[2]
    means <- colMeans(x)
    results <- matrix(0,cols,cols)
    for (i in 1:cols-1)
      for (j in (i+1):cols){
        results[i,j] <- means[i] - means[j]
        results[j,i] <- means[j] - means[i]
      }
    results
  }

  use.huber <- FALSE
  remove.extreme <- match.arg(remove.extreme)

  rows <- dim(x)[1]
  cols <- dim(x)[2]

  if (is.null(weights)){
    weights <- .Call("R_qnorm_robust_weights",x,remove.extreme,as.integer(n.remove),PACKAGE="preprocessCore")
  } else {
    if (is.numeric(weights)){
      if (length(weights) != cols){
        stop("Weights vector incorrect length\n")
      }
      if (sum(weights > 0) < 1){
        stop("Need at least one non negative weights\n")
      }
      if (any(weights < 0)){
        stop("Can't have negative weights")
      }
    } else {
      if (weights =="huber"){
        use.huber <- TRUE
        weights <- rep(1,cols)
      } else {
        stop("Don't recognise weights argument as valid.")
      }
    }
  }
  
  .Call("R_qnorm_robust_c",x,copy,weights,as.integer(use.median),as.integer(use.log2),as.integer(use.huber),PACKAGE="preprocessCore")
}
