generateExprVal.method.playerout <- function(probes, weights=FALSE, optim.method="L-BFGS-B"){
  
  probes <- t(probes)
  nprobes <- ncol(probes)
  
  ## skip if only one probe
  if (nprobes == 1) return(t(probes))
  
  ## I do not know to which extend the use of optim
  ## is really equivalent to the use of nlminb in S-plus
  S1 <- optim(runif(nprobes),
              playerout.costfunction,
              method=optim.method,
              control=list(maxit=500),
              y=probes)
  ##S1 <- nlm(playerout,runif(20),iterlim=500,y=t(y))
  r <- c(probes %*% S1$par / sum(S1$par))
  if (weights)
    attr(r,"weights") <- S1$par
  return(list(exprs=r,se.exprs=rep(NA,length(r))))
}


## The loss function:

playerout.costfunction <- function(w, y) {
  N <- length(w)        # Number of players
  J <- length(y)/N      # Number of games (the number of games is the number of chips used)
  sumw <- sum(w)
  
  tx <- y %*% w    # Full weighted score at each game  
  pl <- matrix(0,J,N)    # Loss at each game due to each player
  
  for(j in 1:J)
    pl[j,] <- w * y[j,] - (tx[j] - w * y[j,]) / (sumw - w)
  
  sum(pl^2)         # Loss
}


