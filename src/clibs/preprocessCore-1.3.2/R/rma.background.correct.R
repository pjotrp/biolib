##################################################################
##
## file: rma.background.correct.R
##
## implements the normal boackground + exponential signal background
## correction traditionally used in RMA computations
##
## for more details see
##  Bolstad, BM (2004) Low Level Analysis of High-density Oligonucleotide Array Data: Background, Normalization and Summarization. Dissertation. University of California, Berkeley.
## pages 17-21
##
##
## History 
## Mar 22, 2008 - Initial version (in preprocessCore)
##
##

rma.background.correct <- function(x,copy=TRUE){

  rows <- dim(x)[1]
  cols <- dim(x)[2]

  if (!is.matrix(x)){
    stop("Matrix expected in normalize.quantiles")
  }

  if (is.integer(x)){
    x <- matrix(as.double(x),rows,cols)
    copy <- FALSE
  }

  .Call("R_rma_bg_correct", x, copy, PACKAGE="preprocessCore");
}





















