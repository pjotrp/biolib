###these are summary functions they take matrices of probes x chips
###and return expression and se (when applicable)

##DEBUG: appending the se to the expression values in a same vector
##       is too much hackish (I think)... we need to think about something
##       better

avdiff <- function(x,constant=3){
  e <- apply(x,2,function(y){
    o <- order(y)
    yy <- y[-c(o[1],o[length(y)])] #take out biggest and smallest
    if(length(yy)<2)  # SK, some genes have only one probe
      mean(y)
    else
      mean(y[abs(y-mean(yy))<constant*sd(yy)])
  })
  list(exprs=e,se.exprs=apply(x,2,sd)/sqrt(nrow(x)))
}

li.wong <- function(data.matrix,remove.outliers=TRUE,
                    normal.array.quantile=0.5,
                    normal.resid.quantile=0.9,
                    large.threshold=3,
                    large.variation=0.8,
                    outlier.fraction=0.14,
                    delta = 1e-06,maxit=50,outer.maxit=50,verbose=FALSE){

  e <-  fit.li.wong(t(data.matrix),remove.outliers,normal.array.quantile,normal.resid.quantile,large.threshold,large.variation,outlier.fraction,delta,maxit,outer.maxit,verbose)
  list(exprs=e$theta,se.exprs=e$sigma.theta)
}


medianpolish <- function(x, ...){
  tmp <- medpolish(log2(x), trace.iter=FALSE, ...)
  ##rough estimate
  sigma <- 1.483*median(abs(as.vector(tmp$residuals)))/sqrt(nrow(x))
  list(exprs=tmp$overall + tmp$col,se.exprs=rep(sigma, ncol(x)))
}

tukeybiweight <- function(x, c=5, epsilon=0.0001){
  tmp <- function(x, c=5, epsilon=0.0001)
    {
      m <- median(x)
      s <- median(abs(x - m))
      u <- (x - m) / (c * s + epsilon)
      w <- rep(0, length(x))
      i <- abs(u) <= 1
      w[i] <- ((1 - u^2)^2)[i]
      t.bi <- sum(w * x) / sum(w)
      return(t.bi)
    }
  list(exprs=apply(log2(x),2,tmp),se.exprs=rep(NA,ncol(x)))
}


