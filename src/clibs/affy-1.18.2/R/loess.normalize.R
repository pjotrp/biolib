loess.normalize <- function(mat,subset=sample(1:(dim(mat)[2]),5000),
                      epsilon=10^-2,maxit=1,log.it=TRUE,verbose=TRUE,span=2/3,
                      family.loess="symmetric"){
  J <- dim(mat)[2]
  II <- dim(mat)[1]
  newData <- mat
  if(log.it){
    mat <- log2(mat)
    newData <- log2(newData)
  }
  change <- epsilon +1
  fs <- matrix(0,II,J)##contains what we substract
  iter <- 0
  w <- c(0,rep(1,length(subset)),0) ##this way we give 0 weight to the
  ##extremes added so that we can interpolate
  while(iter < maxit){
    iter <- iter+1
    means <- matrix(0,II,J) ##contains temp of what we substract
    for(j in 1:(J-1)){
      for(k in (j+1):J){
        y <- newData[,j]-newData[,k]
        x <-(newData[,j]+newData[,k])/2
        index <- c(order(x)[1],subset,order(-x)[1])
        ##put endpoints in so we can interpolate
        xx <- x[index]
        yy <- y[index]
        aux <-loess(yy~xx,span=span,degree=1,weights=w,family=family.loess)
        aux <- predict(aux,data.frame(xx=x))/J
        means[,j] <- means[,j] + aux
        means[,k] <- means[,k] - aux
        if(verbose) cat("Done with",j,"vs",k," in iteration ",iter,"\n")
      }
    }
    fs <- fs+means
    newData <- mat-fs
    change <- max(colMeans((means[subset,])^2))
    if(verbose) cat(iter,change,"\n")
    oldfs <- fs
  }
  if(change>epsilon & maxit>1) warning(paste("No convergence after",maxit,"iterations.\n"))
  if(log.it) return(2^newData)
  else return(newData)
}


