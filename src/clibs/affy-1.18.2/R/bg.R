####These functions take an AffyBatch object "background correct"
####the pms and return an AffyBatch with the background corrected PMs
###
bg.parameters <- function(pm, n.pts=2^14){
  
  max.density <- function(x, n.pts){
    aux <- density(x, kernel="epanechnikov", n=n.pts, na.rm=TRUE)
    aux$x[order(-aux$y)[1]] 
  }
  
  pmbg <- max.density(pm,n.pts) ##Log helps detect mode
  bg.data <- pm[pm < pmbg]
  ##do it again to really get the mode
  pmbg <- max.density(bg.data,n.pts) 
  bg.data <- pm[pm < pmbg]
  bg.data <- bg.data - pmbg
  
  bgsd <- sqrt(sum(bg.data^2)/(length(bg.data)-1))*sqrt(2)#/.85
  
  sig.data <- pm[pm > pmbg]
  sig.data <- sig.data-pmbg
  
  expmean <- max.density(sig.data,n.pts)
  alpha <- 1/expmean
  mubg <- pmbg
  list(alpha=alpha,mu=mubg,sigma=bgsd)  
}

bg.adjust <- function(pm, n.pts=2^14, ...){
  param <- bg.parameters(pm,n.pts)
  b <- param$sigma
  pm <- pm - param$mu - param$alpha*b^2
  pm + b*((1./sqrt(2*pi))*exp((-1./2.)*((pm/b)^2)))/pnorm(pm/b)
}

bg.correct.none <- function(object, ...)
  object

##bg.correct.subtractmm <- function(object){
##  pm(object) <- pm(object) - mm(object)
##  return(object)
##}

###bg.correct.rma <- function(object, ...){
###  pm(object) <- apply(pm(object),2,bg.adjust)
###  return(object)
##}

##
## this function calls the c code as an alternative to the R code above.
## it should help end the disagreement between rma() and expresso()
##

bg.correct.rma <- function(object,...){
  
	pm(object) <- rma.background.correct(pm(object),copy=FALSE)
        return(object)
}

## --- pmcorrect things

pmcorrect.subtractmm <- function(object){
  pm.corrected <- pm(object) - mm(object)
  return(pm.corrected)
}

pmcorrect.pmonly <- function(object) {
  return(pm(object))
}







