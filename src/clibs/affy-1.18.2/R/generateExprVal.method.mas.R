generateExprVal.method.mas <- function(probes, ...)
{
  
  probes <- log2(probes)
  M <-  ncol(probes)
  slg <- rep(NA,M)
  
  for (i in 1:ncol(probes)) {
    
    slg[i] <- tukey.biweight(probes[ ,i], ...)
    
  }
  
  return(list(exprs=2^slg,se.exprs=rep(NA,M)))
    
}

affy.scalevalue.exprSet <- function(eset, sc=500, analysis="absolute")
{
  
  analysis <- match(analysis, c("absolute", "comparison"))
  
  if(analysis == 1)
    nf <- 1
  else
    stop("sorry! comparison not implemented.")
  for (i in 1:ncol(exprs(eset))) {
    slg <- exprs(eset)[, i]
    sf <- sc / mean(slg, trim=0.02)  
    reported.value <- nf * sf * slg
    exprs(eset)[, i] <- reported.value
  }
  
  return(eset)
}
