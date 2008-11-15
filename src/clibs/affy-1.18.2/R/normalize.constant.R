normalize.AffyBatch.constant <- function(abatch, refindex=1, FUN=mean, na.rm=TRUE) {
  
  n <- length( abatch )
  
  if (! (refindex %in% 1:n)) stop("invalid reference index for normalization")
  refconstant <- FUN(intensity(abatch)[,refindex], na.rm=na.rm)
  
  #set.na.spotsd(abatch)

  normhisto <- vector("list", length=n)
  for (i in (1:n)[-refindex]) {
    m <- normalize.constant(intensity(abatch)[,i], refconstant, FUN=FUN, na.rm=na.rm)
    myhistory <- list(name="normalized by constant",
                      constant=attr(m,"constant"))
    attr(m,"constant") <- NULL
    intensity(abatch)[, i] <- m
    normhisto[[i]] <- myhistory
  }
  attr(abatch, "normalization") <- normhisto
  return(abatch)
}       


normalize.constant <- function(x, refconstant, FUN=mean, na.rm=TRUE) {
  thisconstant <- FUN(x, na.rm=na.rm)
  r <- x / thisconstant * refconstant
  attr(r,"constant") <- thisconstant * refconstant
  return(r)
}




