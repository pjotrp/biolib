normalize.AffyBatch.contrasts <- function(abatch,span=2/3,choose.subset=TRUE,subset.size=5000,verbose=TRUE,family="symmetric",type=c("together","pmonly","mmonly","separate")) {

  type <- match.arg(type)
  
  if (type == "pmonly"){
    Index <- unlist(pmindex(abatch))
  } else if (type == "mmonly"){
    Index <- unlist(mmindex(abatch))
  } else if (type == "together"){
    Index <- unlist(indexProbes(abatch,"both"))
  } else if (type == "separate"){
    abatch <- normalize.AffyBatch.contrasts(abatch,span=span,choose.subset=choose.subset,subset.size=subset.size,verbose=verbose,family=family,type="pmonly")
    Index <- unlist(mmindex(abatch))
  }
  
  ##we need default argumetns becuase they are used in this transitional file
  alldata <- intensity(abatch)[Index,]
  
  if(choose.subset)
    subset1 <- maffy.subset(alldata,verbose=verbose,subset.size=subset.size)$subset
  else
    subset1 <- sample(1:dim(alldata)[1],subset.size)
  aux <-   maffy.normalize(alldata,subset=subset1,verbose=verbose,span=span,family=family)
  
  intensity(abatch)[Index,] <- aux

  ##attr(abatch, "normalization") <- normhisto
  return(abatch)
}









