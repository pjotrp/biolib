##
## file: colSummarize.R
##
## Author: B. M. Bolstad <bmb@bmbolstad.com>
##
## History
## Sept 15, 2007 - Initial verison
##




colSummarizeAvgLog <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")
  
  .Call("R_colSummarize_avg_log",y,PACKAGE="preprocessCore")
}


colSummarizeLogAvg <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")
  
  .Call("R_colSummarize_log_avg",y,PACKAGE="preprocessCore")
}


colSummarizeAvg <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")
  
  .Call("R_colSummarize_avg",y,PACKAGE="preprocessCore")
}


colSummarizeLogMedian <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")
  
  .Call("R_colSummarize_log_median",y,PACKAGE="preprocessCore")
}




colSummarizeMedianLog <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")
  
  .Call("R_colSummarize_median_log",y,PACKAGE="preprocessCore")
}


colSummarizeMedian <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")
  
  .Call("R_colSummarize_median",y,PACKAGE="preprocessCore")
}



colSummarizeBiweightLog <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")
  
  .Call("R_colSummarize_biweight_log",y,PACKAGE="preprocessCore")
}

colSummarizeBiweight <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")
  
  .Call("R_colSummarize_biweight",y,PACKAGE="preprocessCore")
}



colSummarizeMedianpolishLog <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")
  
  .Call("R_colSummarize_medianpolish_log",y,PACKAGE="preprocessCore")
}


colSummarizeMedianpolish <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")
  
  .Call("R_colSummarize_medianpolish",y,PACKAGE="preprocessCore")
}



