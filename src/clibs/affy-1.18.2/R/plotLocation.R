plotLocation <- function(x, col="green", pch=22, ...) {
  if (is.list(x)) {
    x <- cbind(unlist(lapply(x, function(x) x[,1])),
               unlist(lapply(x, function(x) x[,2])))
  }
  points(x[,1], x[,2]
         , pch=pch, col=col, ...)
}
