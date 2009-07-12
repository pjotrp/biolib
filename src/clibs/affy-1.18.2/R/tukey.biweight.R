tukey.biweight <- function(x, c=5, epsilon=0.0001)
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

tukeybiweight <-  function(x, c=5, epsilon=0.0001)
  list(exprs=apply(x,2,tukey.biweight,c=c,epsilon=epsilon),se.exprs=rep(NA,ncol(x)))


