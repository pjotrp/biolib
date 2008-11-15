fit.li.wong <- function(data.matrix, remove.outliers=TRUE,
                        normal.array.quantile=0.5,
                        normal.resid.quantile=0.9,
                        large.threshold=3,
                        large.variation=0.8,
                        outlier.fraction=0.14,
                        delta = 1e-06,maxit=50,outer.maxit=50, verbose=FALSE, ...){
  if(missing(data.matrix)) stop("Argument data.matrix missing, with no default")
  II <- dim(data.matrix)[1] ##II instrad of I cause I is a fuction in R
  J <- dim(data.matrix)[2]
  if(J==1){
    warning("Li and Wong's algorithm is not suitable when only one probe pair")
    return(list(theta = as.vector(data.matrix), phi = 1, sigma.eps = NA, sigma.theta = NA, sigma.phi=NA, theta.outliers=NA, phi.outliers=NA, single.outliers=NA,convergence1=NA,convergence2=NA,iter = NA, delta = NA))
  }
  cI <- II ##current I
  cJ <- J ##current J
  theta.outliers.old <- rep(FALSE, II) ##ith entry will be true if theta_i is an outlier
  phi.outliers.old <- rep(FALSE, J) ##jth entry will be true if phi_j is an outlier
  single.outliers.old <- matrix(FALSE, II, J) ##ij entry will be true if y_is an outlier
  theta.outliers <- theta.outliers.old ##need this to now if change ocurred in outliers
  phi.outliers <- phi.outliers.old ##need this to know if chages occured in outlies
  single.outliers <- single.outliers.old
  flag1 <- NA ##these will be false if convergence not reacher,
  flag2 <- NA ## this will be false if outliers respectively cuase iter to stop
  if(remove.outliers){
    flag1 <- TRUE; flag2<-TRUE
    original.data.matrix <- data.matrix ##so we can get it back after outlier removal
    change.theta <- 1 #start with 1
    change.phi <- 1
    change.single <- 1
    outer.iter <- 0
    while(flag1 & flag2 & change.theta+change.phi+change.single >0 & outer.iter < outer.maxit) {
      outer.iter <- outer.iter + 1

      if((outer.iter%%3==0 & change.theta>0)  |
         (outer.iter%%3==1 & change.phi>0)){ #something has to change
        ##starting values
        phi <- colMeans(data.matrix)
        c <- sqrt(cJ/sum(phi[!phi.outliers]^2))
        phi <- c * phi
        theta <- (data.matrix[, !phi.outliers, drop=FALSE] %*% phi[!phi.outliers, drop=FALSE])/cJ
        iter <- 0
        change <- 1 #start with one
        theta.old <- rep(0, II)
        while(change > delta & iter < maxit) {
          iter <- iter + 1
          phi <- t(data.matrix[!theta.outliers, ,drop=FALSE]) %*% theta[!theta.outliers, drop=FALSE] ##ignore the outliers
          c <- sqrt(cJ/sum(phi[!phi.outliers, drop=FALSE]^2))
          phi <- c * phi
          theta <- (data.matrix[,!phi.outliers, drop=FALSE] %*% phi[!phi.outliers, drop=FALSE])/cJ
          change <- max(abs(theta[!theta.outliers] - theta.old[!theta.outliers]))
          if(verbose) cat(paste("Outlier iteration:",outer.iter,"estimation iteration:",iter,"chage=",change,"\n"))
          theta.old <- theta
        }
        if(iter>=maxit){ ##convergence not reached. might as well get out
          warning(paste("No convergence in inner loop after",iter,"in outerler tieration",outer.iter,"\n"))
          flag1 <- FALSE
        }
        if(mean(phi[!phi.outliers]<0)>.5){ ##for identifiability.. theta*phi = (-theta)*(-phi), i require that most phis are positive
          theta <- -theta
          phi <- -phi
        }
        theta <- as.vector(theta)
        phi <- as.vector(phi)

        data.matrixhat <- outer(theta, phi)
        resid <- data.matrix-data.matrixhat
      }
      ##DEALING WITH OUTLIERS
      ##we alternate removal of outliers
      ##if even iteration take out thetas that are outliers (as defined by Li and Wong).
      if(outer.iter%%3==1){ ## we start with single outliers
        single.outliers <- resid > large.threshold*quantile(abs(resid),normal.resid.quantile)
        single.outliers[rowSums(single.outliers) > outlier.fraction*cJ,]<-rep(FALSE,J)
        ##probably chip oulier, defer calling outlier
        single.outliers[,colSums(single.outliers) > outlier.fraction*cI]<-rep(FALSE,II)
        ##probably probe outlier, defer calling outlier
        data.matrix[single.outliers] <- data.matrixhat[single.outliers]
        data.matrix[!single.outliers] <- original.data.matrix[!single.outliers]
        change.single <- sum(abs(single.outliers.old-single.outliers)) #sum will be total of changes
        single.outliers.old <- single.outliers
      }
      else{
        sigma.theta <- sqrt(rowSums(resid[, !phi.outliers, drop=FALSE]^2)/(cJ - 1))
        sigma.phi <- sqrt(colSums(resid[!theta.outliers, , drop=FALSE]^2)/(cI - 1))
        ###THETA OUTLIERS
        if(outer.iter%%3==2){
          theta.outliers <- sigma.theta > large.threshold*quantile(sigma.theta,normal.array.quantile) | theta^2/sum(theta^2) > large.variation
          cI <- sum(!theta.outliers)
          if(cI<3) {
            warning("No convergence achieved, too many outliers")
            flag2 <- FALSE
          }
          ##single outliers in outlier chips are not longer single outliers
          single.outliers[theta.outliers,] <- rep(FALSE,J)
          data.matrix[single.outliers] <- data.matrixhat[single.outliers]
          data.matrix[!single.outliers]<-original.data.matrix[!single.outliers]
          change.theta <- sum(abs(theta.outliers.old-theta.outliers)) #sum will be total of changes
          change.single <- sum(abs(single.outliers.old-single.outliers)) #sum will be total of changes
          theta.outliers.old <- theta.outliers
        }
        ##PHI OUTLIERS
        else{
          phi.outliers <- sigma.phi > large.threshold*quantile(sigma.phi,normal.array.quantile) | phi^2/sum(phi^2) > large.variation | phi <0
          cJ <- sum(!phi.outliers)
          if(cJ<3) {
            warning("No convergence achieved, too many outliers")
            flag2 <- FALSE
          }
          single.outliers[,phi.outliers] <- rep(FALSE,II)
          data.matrix[single.outliers] <- data.matrixhat[single.outliers]
          data.matrix[!single.outliers]<-original.data.matrix[!single.outliers]
          change.phi <- sum(abs(phi.outliers.old-phi.outliers))
          change.single <- sum(abs(single.outliers.old-single.outliers)) #sum will be total of changes
          phi.outliers.old <- phi.outliers
        }
      }
      if(verbose){
        cat("chips used=",cI,", probes used=",cJ,", single outler=",sum(single.outliers),"\n")
        cat("Number of changes: single=",change.single,", theta=",change.theta,", phi=",change.phi,"\n",sep="")
      }
    }
    if(outer.iter>=outer.maxit){
      warning("No convergence achieved in outlier loop\n")
      flag2 <- FALSE
    }
    all.outliers <- outer(theta.outliers,phi.outliers,FUN="|") | single.outliers
    sigma <- sqrt(sum(resid[!all.outliers]^2)/sum(!all.outliers))
    ##in case we leave iteration and these havent been defined
    sigma.theta <- sqrt(rowSums(resid[,!phi.outliers, drop=FALSE]^2)/(cJ - 1))
    sigma.phi <- sqrt(colSums(resid[!theta.outliers, ,drop=FALSE]^2)/(cI - 1))
  }
  ###code for NO OUTLIER REMOVAL
  else{
    flag1 <- TRUE
    phi <- colMeans(data.matrix)
    c <- sqrt(J/sum(phi^2))
    phi <- c * phi
    theta <- (data.matrix %*% phi)/J

    iter <- 0
    change <- 1
    theta.old <- rep(0, II)
    while(change > delta & iter < maxit) {
      iter <- iter + 1
      phi <- t(data.matrix) %*% theta
      c <- sqrt(J/sum(phi^2))
      phi <- c * phi
      theta <- (data.matrix %*% phi)/J
      change <- max(abs(theta - theta.old))
      if(verbose) cat(paste("Iteration:",iter,"chage=",change,"\n"))
      theta.old <- theta
    }
    if(iter>=maxit){
      warning(paste("No convergence after",iter,"iterations.\n"))
      flag1 <- FALSE
    }
    if(mean(phi[!phi.outliers]<0)>.5){
      ##for identifiability.. theta*phi = (-theta)*(-phi), i require that most phis are positive
      theta <- -theta
      phi <- -phi
    }
    theta <- as.vector(theta)
    phi <- as.vector(phi)
    data.matrixhat <- outer(theta, phi)
    sigma.theta <- sqrt(rowSums((data.matrix - data.matrixhat)^2)/(J - 1))
    sigma.phi <- sqrt(colSums((data.matrix - data.matrixhat)^2)/(II - 1))
    sigma <- sqrt(sum((data.matrix - data.matrixhat)^2)/(II * J))
  }
  return(list(theta = theta, phi = phi, sigma.eps = sigma, sigma.theta = sigma.theta, sigma.phi=sigma.phi,theta.outliers=theta.outliers,phi.outliers=phi.outliers,single.outliers=single.outliers,convergence1=flag1,convergence2=flag2,iter = iter, delta = change))
}
