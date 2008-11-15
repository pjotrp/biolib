avdiff <- function(x,verbose=FALSE){
  if(missing(x)) stop("Argument x missing, with no default\n")
  cat("Computing average difference for",dim(x$pm)[2],"columns")
  avdiff <- apply(x$pm-x$mm,2,function(y){
    cat(".")
    tapply(y,x$name,function(z){
      o <- order(z)
      zz <- z[-c(o[1],o[length(z)])] #take out biggest and smallest
      mean(z[abs(z-mean(zz))<3*sd(zz)])
    })
  })
  colnames(avdiff) <- x$chip.names
  return(avdiff)
}
