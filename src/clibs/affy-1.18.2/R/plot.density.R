# matdensity <- function(x,
#                        ylab="density", xlab="x", type="l", plot=TRUE,
#                        ...) {
  
#   x.density <- apply(mat, 2, density)

#   all.x <- do.call("cbind", lapply(x.density, function(x) x$x))
#   all.y <- do.call("cbind", lapply(x.density, function(x) x$y))
  
#   if (plot)
#     matplot(all.x, all.y, ylab=ylab, xlab=xlab, ...)
 
#   invisible(list(all.x=all.x, all.y=all.y))                     
                       
# }

plotDensity <- function(mat,
                        ylab="density", xlab="x", type="l", col=1:6,
                        na.rm = TRUE,
                        ...) {
  
  x.density <- apply(mat, 2, density, na.rm = na.rm)

  all.x <- do.call("cbind", lapply(x.density, function(x) x$x))
  all.y <- do.call("cbind", lapply(x.density, function(x) x$y))
  
  matplot(all.x, all.y, ylab=ylab, xlab=xlab, type=type, col=col, ...)

  invisible(list(all.x=all.x, all.y=all.y))
}
 

plotDensity.AffyBatch <- function(x, col=1:6, log=TRUE,
                                  which=c("pm","mm","both"),
                                  ylab="density",
                                  xlab=NULL,
                                  ...){
  
  Index <- unlist(indexProbes(x, which=which))
  
  x <- intensity(x)[Index, ,drop=FALSE]
  
  if(log){
    x <- log2(x)
    if(is.null(xlab)) xlab <- "log intensity"
  }
  else  if(is.null(xlab)) xlab <- "intensity"
  
  invisible(plotDensity(x, ylab=ylab, xlab=xlab, col=col, ...))

}
