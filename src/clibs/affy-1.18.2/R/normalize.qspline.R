normalize.AffyBatch.qspline <- function(abatch, type=c("together","pmonly","mmonly","separate"),...) {

  type <- match.arg(type)

  if (type == "together"){
    Index <- unlist(indexProbes(abatch,"both"))
    intensity(abatch)[Index,] <- normalize.qspline(intensity(abatch)[Index,], ...)
  } else if (type == "pmonly"){
    Index <- unlist(indexProbes(abatch,"pm"))
    intensity(abatch)[Index,] <- normalize.qspline(intensity(abatch)[Index,], ...)
  } else if (type == "mmonly"){
    Index <- unlist(indexProbes(abatch,"mm"))
    intensity(abatch)[Index,] <- normalize.qspline(intensity(abatch)[Index,], ...)
  } else if (type == "separate"){
    Index <- unlist(indexProbes(abatch,"pm"))
    intensity(abatch)[Index,] <- normalize.qspline(intensity(abatch)[Index,], ...)
    Index <- unlist(indexProbes(abatch,"mm"))
    intensity(abatch)[Index,] <- normalize.qspline(intensity(abatch)[Index,], ...)
  }
  #set.na.spotsd(listcel)
  normhisto <- vector("list", length=ncol(intensity(abatch)))
  ##need to use MIAME for this
  for (i in 1:length(abatch)) {
    normhisto[[i]] <- list(name="normalized by qspline")
  }

  attr(abatch, "normalization") <- normhisto

  return(abatch)
}

normalize.qspline <- function(x,
                              target        = NULL,
                              samples       = NULL,
                              fit.iters     = 5,
                              min.offset    = 5,
                              spline.method = "natural", # c("fmm", "natural", "periodic")
                              smooth        = TRUE,
                              spar          = 0,     # smoothing parameter
                              p.min         = 0,
                              p.max         = 1.0,
                              incl.ends     = TRUE,
                              converge      = FALSE,
                              verbose       = TRUE,
                              na.rm         = FALSE
                              ){

  if (is.null(target))
    target <- exp(apply(log(x), 1, mean))

  x.n <- dim(x)[1]
  m   <- dim(x)[2]

  if (is.null(samples))
    samples <- max(round(x.n/1000), 100)
  else
    if (samples < 1)
      samples <- round(samples * x.n)

  p <- (1:samples) / samples
  p <- p[ which(p <= p.max) & which(p >= p.min) ]
  samples <- length(p)

  k <- fit.iters

  if (na.rm==TRUE)
    y.n <- sum(!is.na(target))
  else
    y.n <- length(target)

  py.inds  <- as.integer(p * y.n)
  y.offset <- round(py.inds[1]/fit.iters)

  if (y.offset <= min.offset) {
    y.offset <- min.offset;
    k <- round(py.inds[1]/min.offset)
  }

  if (k <= 1) {
    warning("'k' found is non-sense. using default 'fit.iter'")
    k <- fit.iters
  }

  y.offset <- c(0, array(y.offset, (k-1)))
  y.order <- order(target)

  fx <- matrix(0, x.n,m)
  if(verbose==TRUE)
    print(paste("samples=",samples, "k=", k, "first=", py.inds[1]))

  for (i in 1:m) {
                                        # to handel NA values for each array
    if (na.rm==TRUE)
      x.valid <- which(!is.na(x[,i]))
    else
      x.valid <- 1:x.n

    x.n <- length(x.valid)
    px.inds  <- as.integer(p * x.n)
      x.offset <- round(px.inds[1]/fit.iters)

    if (x.offset<=min.offset) {
      x.offset <- min.offset;
      k <- min(round(px.inds[1]/min.offset), k)
    }

    x.offset <- c(0, array(x.offset, (k-1)))
    x.order  <- order(x[,i]) # NA's at the end (?)

    y.inds   <- py.inds ## must be reset each iteration
    x.inds   <- px.inds

    for (j in 1:k) {
         y.inds <- y.inds - y.offset[j]
         x.inds <- x.inds - x.offset[j]
         ty.inds <- y.inds
         tx.inds <- x.inds
         if (verbose==TRUE)
           print(paste("sampling(array=", i, "iter=", j, "off=",
                       x.inds[1], -x.offset[j], y.inds[1], -y.offset[j], ")"))

         if (converge==TRUE) {
           ty.inds <- as.integer(c(1, y.inds))
           tx.inds <- as.integer(c(1, x.inds))

           if (j > 1) {
             ty.inds <- c(ty.inds, y.n)
             tx.inds <- c(tx.inds, x.n)
           }
         }
         qy <- target[y.order[ty.inds]]
         qx <-  x[x.order[tx.inds],i]

         if (smooth==TRUE) {
           sspl <- smooth.spline(qx, qy, spar=spar)
           qx <- sspl$x
           qy <- sspl$y
         }

         fcn <- splinefun(qx, qy, method=spline.method)
         fx[x.valid,i] <- fx[x.valid,i] + fcn(x[x.valid,i])/k
       }

    if (na.rm==TRUE) {
      invalid <- which(is.na(x[,i]))
      fx[invalid,i] <- NA
    }
  }
  return(fx)
}
