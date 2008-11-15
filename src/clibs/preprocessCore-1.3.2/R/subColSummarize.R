##
## file: subColSummarize.R
##
## Author: B. M. Bolstad <bmb@bmbolstad.com>
##
## History
## Sept 18, 2007 - Initial verison
## Dec 10, 2007 - add rownames to output
##


convert.group.labels <- function(group.labels){

  if (!is.factor(group.labels))
    group.labels <- as.factor(group.labels)

  split(0:(length(group.labels) -1),group.labels)

}




subColSummarizeAvgLog <- function(y, group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")

  rowIndexList <- convert.group.labels(group.labels)
  
  x <- .Call("R_subColSummarize_avg_log", y, rowIndexList, PACKAGE="preprocessCore")

  rownames(x) <- names(rowIndexList)
  x
}





subColSummarizeLogAvg <- function(y, group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")

  rowIndexList <- convert.group.labels(group.labels)
  
  x <- .Call("R_subColSummarize_log_avg", y, rowIndexList, PACKAGE="preprocessCore")
  rownames(x) <- names(rowIndexList)
  x
}




subColSummarizeAvg <- function(y, group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")

  rowIndexList <- convert.group.labels(group.labels)
  
  x <- .Call("R_subColSummarize_avg", y, rowIndexList, PACKAGE="preprocessCore")
  rownames(x) <- names(rowIndexList)
  x
  
}




subColSummarizeBiweightLog <- function(y, group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")

  rowIndexList <- convert.group.labels(group.labels)
  
  x <- .Call("R_subColSummarize_biweight_log", y, rowIndexList, PACKAGE="preprocessCore")
  rownames(x) <- names(rowIndexList)
  x
}




subColSummarizeBiweight <- function(y, group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")

  rowIndexList <- convert.group.labels(group.labels)
  
  x <- .Call("R_subColSummarize_biweight", y, rowIndexList, PACKAGE="preprocessCore")
  rownames(x) <- names(rowIndexList)
  x


}





subColSummarizeMedianLog <- function(y, group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")

  rowIndexList <- convert.group.labels(group.labels)
  
  x <- .Call("R_subColSummarize_median_log", y, rowIndexList, PACKAGE="preprocessCore")
  rownames(x) <- names(rowIndexList)
  x
}





subColSummarizeLogMedian <- function(y, group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")

  rowIndexList <- convert.group.labels(group.labels)
  
  x <- .Call("R_subColSummarize_log_median", y, rowIndexList, PACKAGE="preprocessCore")
  rownames(x) <- names(rowIndexList)
  x
}




subColSummarizeMedian <- function(y, group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")

  rowIndexList <- convert.group.labels(group.labels)
  
  x <- .Call("R_subColSummarize_median", y, rowIndexList, PACKAGE="preprocessCore")
  rownames(x) <- names(rowIndexList)
  x
}







subColSummarizeMedianpolishLog <- function(y, group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")

  rowIndexList <- convert.group.labels(group.labels)
  
  x <- .Call("R_subColSummarize_medianpolish_log", y, rowIndexList, PACKAGE="preprocessCore")
  rownames(x) <- names(rowIndexList)
  x
}


subColSummarizeMedianpolish <- function(y, group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (!is.double(y) & is.numeric(y))
    y <- matrix(as.double(y),dim(y)[1],dim(y)[2])
  else if (!is.numeric(y))
    stop("argument should be numeric matrix")

  rowIndexList <- convert.group.labels(group.labels)
  
  x <- .Call("R_subColSummarize_medianpolish", y, rowIndexList, PACKAGE="preprocessCore")
  rownames(x) <- names(rowIndexList)
  x
}

