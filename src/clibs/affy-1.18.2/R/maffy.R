##*******************************************************************************************
#**********  maffy.normalize     *****
maffy.normalize <- function(data,subset,verbose=FALSE,span=0.25,family="symmetric",log.it=TRUE){

k <- dim(data)[2]   ### Number of chips

####   Create the transformation matrix
t1 <- 1/sqrt(k)
t2 <- (k-2-t1)/(k-1)
t3 <- -(1+t1)/(k-1)

transmat <- matrix(t3,k,k)
for(i in 1:k){
     transmat[1,i]<-t1
     transmat[i,1]<-t1
}
for(i in 2:k) transmat[i,i]<-t2

#### Find normalizing curve

if(verbose) cat("Fitting normalizing curve\n")
n<- length(subset)
data.subset <- data[subset,]

data.subset <- log(data.subset)%*%t(transmat)
index <- order(data.subset[,1])
data.subset <- data.subset[index,]

if( k>2) curve <- multiloess(data.subset[,2:k]~data.subset[,1],span=span,family=family,surface="direct")
else     curve <-      loess(data.subset[,2:k]~data.subset[,1],span=span,family=family,surface="direct")

### Transform the normalizing curve before and after normalization
scaled   <- cbind(data.subset[,1],matrix(0,n,k-1)) %*%(transmat)
unscaled <- cbind(data.subset[,1],curve$fitted)      %*%(transmat)

w <-c(0,rep(1,n,n),0)

data.scaled <- NULL

### Normalize each array
for(i in 1:k){
    if(verbose) cat("Normalizing chip ",i,"\n")
    if(log.it){
        mini  <- log(min(data[,i]))
        maxi  <- log(max(data[,i]))
    }
    else{
        mini  <- min(data[,i])
        maxi  <- max(data[,i])
    }

    curve <- loess(c(mini,scaled[,i],maxi)~c(mini,unscaled[,i],maxi),weights=w,span=span)

    if(log.it)
         temp <-  exp(predict(curve,log(data[,i])))
    else
         temp <-      predict(curve,data[,i])

    data.scaled <- cbind(data.scaled,temp)
}

data.scaled

}


##*******************************************************************************************
#**********  Select A subset with small rank-range over arrays  *****

maffy.subset <- function(data,subset.size=5000,maxit=100,subset.delta=max(round(subset.size/100),25),verbose=FALSE){


k     <- dim(data)[2]   ### Number of chips
n     <- dim(data)[1]   ## Size of starting subset, i.e. all rows

if(verbose)
      cat("Data size",n,"x",k,"Desired subset size",subset.size,"+-",subset.delta,"\n")

means <- data%*%(rep(1,k,k)/k)

index0 <- order(means)

data.sorted <- data[index0,]

## Init
set <- rep(TRUE,n,n)      ## Set-indicator
index.set <- 1:n       ## Indexes for subset
nprev <- n+1
iter  <- 1
part.of.n <- 1

## loop
while(nprev>n & n>(subset.size+subset.delta) & iter <maxit){
    if(verbose)
      cat("Comuting ranks of old subset....")
    ranks <-apply(data.sorted[index.set,],2,rank)              ## Compute ranks, chip by chip.
    ranks.range <- apply(ranks,1,function(r) max(r)-min(r) )   ## Range of ranks over chips

    q <-min((n*part.of.n+subset.size)/((1+part.of.n)*n),1)     ## Select quantiles
    low <- quantile(ranks.range[1:(n*0.2)+n*0.0],probs=q,names=FALSE)/n
    high <-quantile(ranks.range[n+1-(1:(n*0.2))],probs=q,names=FALSE)/n

    newset <-  ranks.range < (low*n+(0:(n-1))*(high-low))        ## Set-indicator of new set

    if(sum(newset)<subset.size-subset.delta){                  ## To small?
       part.of.n <- 1+part.of.n
       if(verbose)
         cat("\nSize of newset to small (",sum(newset),"). Increasing part.of.n.\n")
    }
    else{                                                      ## New set OK
       set <- newset
       index.set <- subset(index.set,set)
       index.set <- index.set[!is.na(index.set)]
       nprev <- n
       n <- length(index.set)
       if(verbose)
          cat("Size of new subset: ",n,"\n")
   }

   iter <- iter+1
}
##end loop

if(!iter <maxit) warning("Maximum number of iterations reached, result my not be correct\n")

list(subset=index0[index.set])

}




##*******************************************************************************************
multiloess <-
function(formula, data=NULL, weights, subset, na.action, model = FALSE,
	 span = 0.75, enp.target, degree = 2,
	 normalize = TRUE,
	 family = c("gaussian", "symmetric"),
	 method = c("loess", "model.frame"),
	 control = loess.control(...), ...)
{
    parametric <- FALSE
    drop.square <- FALSE

    mt <- terms(formula, data = data)
    mf <- match.call(expand.dots=FALSE)
    mf$model <- mf$span <- mf$enp.target <- mf$degree <-
	mf$parametric <- mf$drop.square <- mf$normalize <- mf$family <-
	    mf$control <- mf$... <- NULL
    mf[[1]] <- as.name("model.frame")
    mf <- eval(mf, parent.frame())
    if (match.arg(method) == "model.frame") return(mf)
    y <- model.response(mf, "numeric")

    if(is.vector(y))  stop("The respons variable is not a matrix, use loess")

    w <- model.weights(mf)
    if(is.null(w)) w <- rep(1, NROW(y))
    nmx <- as.character(attr(mt, "variables"))[-(1:2)]
    x <- mf[, nmx, drop=FALSE]
    if(any(sapply(x, is.factor))) stop("predictors must all be numeric")
    x <- as.matrix(x)
    D <- ncol(x)
    nmx <- colnames(x)
    names(nmx) <- nmx
    drop.square <- match(nmx, nmx[drop.square], 0) > 0
    parametric <- match(nmx, nmx[parametric], 0) > 0
    if(!match(degree, 0:2, 0)) stop("degree must be 0, 1 or 2")
    iterations <- if(family=="gaussian") 1 else control$iterations
    if(!missing(enp.target))
	if(!missing(span))
	    warning("both span and enp.target specified: span will be used")
	else {				# White book p.321
	    tau <- switch(degree+1, 1, D+1, (D+1)*(D+2)/2) - sum(drop.square)
	    span <- 1.2 * tau/enp.target
	}
    fit <- simplemultiLoess(y, x, w, span, degree,
		       normalize, control$statistics, control$surface,
		       control$cell, iterations, control$trace.hat)
    fit$call <- match.call()
    fit$terms <- mt
    fit$xnames <- nmx
    fit$x <- x
    fit$y <- y
    fit$weights <- w
    if(model) fit$model <- mf
    fit
}



##*******************************************************************************************
simplemultiLoess <- function(y, x, weights, span = 0.75, degree = 2,
	   normalize = TRUE,
	   statistics = "approximate", surface = "interpolate",
	   cell = 0.2, iterations = 1, trace.hat = "exact")
{

    ## Extra init
    parametric <- FALSE
    drop.square <- FALSE

    M <- NCOL(y)
    A <- rep(1,M,M)

    D <- NCOL(x)
    N <- NROW(x)

    fitted.all <- matrix(1,N,M)
    fitted.residuals <- matrix(1,N,M)
    pseudo.resid.all <-  matrix(1,N,M)

    if(!N || !D)	stop("invalid `x'")
    if(!length(y))	stop("invalid `y'")
    x <- as.matrix(x)
    max.kd <-  max(N, 200)
    robust <- rep(1, N)
    divisor<- rep(1, D)
    if(normalize && D > 1) {
	trim <- ceiling(0.1 * N)
	divisor <-
	    sqrt(apply(apply(x, 2, sort)[seq(trim+1, N-trim), , drop = FALSE],
		       2, var))
	x <- x/rep(divisor, rep(N, D))
    }
    sum.drop.sqr <- sum(drop.square)
    sum.parametric <- sum(parametric)
    nonparametric <- sum(!parametric)
    order.parametric <- order(parametric)
    x <- x[, order.parametric]
    order.drop.sqr <- (2 - drop.square)[order.parametric]
    if(degree==1 && sum.drop.sqr)
	stop("Specified the square of a factor predictor to be dropped when degree = 1")
    if(D == 1 && sum.drop.sqr)
	stop("Specified the square of a predictor to be dropped with only one numeric predictor")
    if(sum.parametric == D) stop("Specified parametric for all predictors")

    if(iterations)
    for(j in 1:iterations) {
	robust <- weights * robust
	if(j > 1) statistics <- "none"
	if(surface == "interpolate" && statistics == "approximate")
	    statistics <- if(trace.hat == "approximate") "2.approx"
	    else if(trace.hat == "exact") "1.approx"
	surf.stat <- paste(surface, statistics, sep="/")
        for(k in 1:M) {
        	z <- .C("loess_raw",
			as.double(y[,k]),
			as.double(x),
			as.double(weights),
			as.double(robust),
			as.integer(D),
			as.integer(N),
			as.double(span),
			as.integer(degree),
			as.integer(nonparametric),
			as.integer(order.drop.sqr),
			as.integer(sum.drop.sqr),
			as.double(span*cell),
			as.character(surf.stat),
			fitted.values = double(N),
			parameter = integer(7),
			a = integer(max.kd),
			xi = double(max.kd),
			vert = double(2*D),
			vval = double((D+1)*max.kd),
			diagonal = double(N),
			trL = double(1),
			delta1 = double(1),
			delta2 = double(1),
			as.integer(surf.stat == "interpolate/exact"),
			PACKAGE="stats")
			fitted.all[,k] <- z$fitted.values
	}

	if(j==1) {
	    trace.hat.out <- z$trL
	    one.delta <- z$delta1
	    two.delta <- z$delta2
	}

	residuals.all <- (y-fitted.all)
	fitted.residuals <- sqrt((residuals.all^2)%*%A)

	if(j < iterations)
	    robust <- .Fortran("lowesw",
			       as.double(fitted.residuals),
			       as.integer(N),
			       robust = double(N),
			       integer(N),
			       PACKAGE="stats")$robust
    }
    if(surface == "interpolate")
    {
	pars <- z$parameter
	names(pars) <- c("d", "n", "vc", "nc", "nv", "liv", "lv")
	enough <- (D + 1) * pars["nv"]
	fit.kd <- list(parameter=pars, a=z$a[1:pars[4]], xi=z$xi[1:pars[4]],
		       vert=z$vert, vval=z$vval[1:enough])
    }
    if(iterations > 1) {
        for(k in 1:M) {
		pseudovalues <- .Fortran("lowesp",
					 as.integer(N),
					 as.double(y[,k]),
					 as.double(fitted.all[,k]),
					 as.double(weights),
					 as.double(robust),
					 integer(N),
					 pseudovalues = double(N),
					 PACKAGE="stats")$pseudovalues
		zz <- .C("loess_raw",
			as.double(pseudovalues),
			as.double(x),
			as.double(weights),
			as.double(weights),
			as.integer(D),
			as.integer(N),
			as.double(span),
			as.integer(degree),
			as.integer(nonparametric),
			as.integer(order.drop.sqr),
			as.integer(sum.drop.sqr),
			as.integer(span*cell),
			as.character(surf.stat),
			temp = double(N),
			parameter = integer(7),
			a = integer(max.kd),
			xi = double(max.kd),
			vert = double(2*D),
			vval = double((D+1)*max.kd),
			diagonal = double(N),
			trL = double(1),
			delta1 = double(1),
			delta2 = double(1),
			as.integer(0),
			PACKAGE="stats")
		pseudo.resid.all[,k] <- pseudovalues-zz$temp
	}

	pseudo.resid <- sqrt((pseudo.resid.all^2)%*%A)

    }
    sum.squares <- if(iterations <= 1) sum(weights * fitted.residuals^2)
    else sum(weights * pseudo.resid^2)
    enp <- one.delta + 2*trace.hat.out - N
    s <- sqrt(sum.squares/one.delta)
    pars <- list(robust=robust, span=span, degree=degree, normalize=normalize,
		 parametric=parametric, drop.square=drop.square,
		 surface=surface, cell=cell, family=
		 if(iterations <= 1) "gaussian" else "symmetric",
		 iterations=iterations)
    fit <- list(n=N, fitted=fitted.all, residuals=residuals.all,
		enp=enp, s=s, one.delta=one.delta, two.delta=two.delta,
		trace.hat=trace.hat.out, divisor=divisor)
    fit$pars <- pars
    if(surface == "interpolate") fit$kd <- fit.kd
    class(fit) <- "loess"
    fit

}


##*******************************************************************************************





