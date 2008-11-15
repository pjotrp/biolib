normalize.AffyBatch.invariantset <- function(abatch, prd.td=c(0.003,0.007), verbose=FALSE,baseline.type=c("mean","median","pseudo-mean","pseudo-median"),type=c("separate","pmonly","mmonly","together")) {

  do.normalize.Affybatch.invariantset <- function(abatch, pms, prd.td, baseline.type){


    nc  <-  length(abatch)                                 # number of CEL files

    if (baseline.type == "mean"){
                                        # take as a reference the array having the median overall intensity
      m <- vector("numeric", length=nc)
      for (i in 1:nc)
        m[i] <- mean(intensity(abatch)[pms, i])
      refindex <- trunc(median(rank(m)))
      rm(m)
      baseline.chip <-  c(intensity(abatch)[pms, refindex])
      if (verbose) cat("Data from", sampleNames(abatch)[refindex], "used as baseline.\n")
    }
    else if (baseline.type == "median"){
                                        # take as a reference the array having the median median intensity
      m <- vector("numeric", length=nc)
      for (i in 1:nc)
        m[i] <- median(intensity(abatch)[pms, i])
      refindex <- trunc(median(rank(m)))
      rm(m)
      baseline.chip <-  c(intensity(abatch)[pms, refindex])
      if (verbose) cat("Data from", sampleNames(abatch)[refindex], "used as baseline.\n")
    } else if (baseline.type == "pseudo-mean"){
                                        # construct a psuedo chip to serve as the baseline by taking probewise means
      refindex <- 0
      baseline.chip <- rowMeans(intensity(abatch)[pms,])
    } else if (baseline.type == "pseudo-median"){
    # construct a pseudo chip to serve as the baseline by taking probewise medians
      refindex <- 0
      baseline.chip <- rowMedians(intensity(abatch)[pms,])
    }


  ##set.na.spotsd(cel.container)

    normhisto <- vector("list", length=nc)
#  normhisto[[refindex]] <- list(name="reference for the invariant set")

  ## loop over the CEL files and normalize them

    for (i in (1:nc)) {
      if (i != refindex){
        if (verbose) cat("normalizing array", sampleNames(abatch)[i], "...")

        ##temporary
        tmp <- normalize.invariantset(c(intensity(abatch)[pms, i]),
                                      c(baseline.chip),
                                      prd.td)
                                        #i.set <- which(i.pm)[tmp$i.set]
        tmp <- as.numeric(approx(tmp$n.curve$y, tmp$n.curve$x,
                               xout=intensity(abatch)[pms, i], rule=2)$y)
        attr(tmp,"invariant.set") <- NULL
        intensity(abatch)[pms, i] <- tmp

        ## storing information about what has been done
                                        #normhisto[[i]] <- list(name="normalized by invariant set",
                                        #                       invariantset=i.set)

        if (verbose) cat("done.\n")

      }
    }
    attr(abatch, "normalization") <- normhisto
    return(abatch)
  }

  type <- match.arg(type)
  baseline.type <- match.arg(baseline.type)

  if (type == "pmonly"){
    pms <- unlist(pmindex(abatch))
    do.normalize.Affybatch.invariantset(abatch, pms, prd.td, baseline.type)
  } else if (type == "mmonly"){
    pms <- unlist(mmindex(abatch))
    do.normalize.Affybatch.invariantset(abatch, pms, prd.td, baseline.type)
  } else if (type == "together"){
    pms <- unlist(indexProbes(abatch,"both"))
    do.normalize.Affybatch.invariantset(abatch, pms, prd.td, baseline.type)
  } else if (type == "separate"){
    pms <- unlist(pmindex(abatch))
    abatch <- do.normalize.Affybatch.invariantset(abatch, pms, prd.td, baseline.type)
    pms <- unlist(mmindex(abatch))
    do.normalize.Affybatch.invariantset(abatch, pms, prd.td, baseline.type)
  }

}



##  The 'common-to-all' part of the algorithm. Operates on two vectors of numeric data
##
normalize.invariantset <- function(data, ref, prd.td=c(0.003,0.007)) {

  np <- length(data)
  r.ref <- rank(ref)
  r.array <- rank(data)

  ## init
  prd.td.adj <- prd.td*10                           # adjusted threshold things
  i.set <- rep(TRUE, np)                            # index all the PM probes as being in the invariant set
  ns <- sum(i.set)                                  # number of probes in the invariant set
  ns.old <- ns+50+1                                 # number of probes previously in the invariant set

  ## iterate while the number of genes in the invariant set (ns) still varies...
  while ( (ns.old-ns) > 50 ) {
    air <- (r.ref[i.set] + r.array[i.set]) / (2*ns)  # average intensity rank for the probe intensities
    prd <- abs(r.ref[i.set] - r.array[i.set]) / ns
    threshold <- (prd.td.adj[2]-prd.td[1]) * air + prd.td.adj[1]
    i.set[i.set] <- (prd < threshold)

    ns.old <- ns
    ns <- sum(i.set)

    if (prd.td.adj[1] > prd.td[1])
      prd.td.adj <- prd.td.adj * 0.9  # update the adjusted threshold parameters
  }

  ## the index i.set corresponds to the 'invariant genes'
  n.curve <- smooth.spline(ref[i.set], data[i.set])
  ## n.curve$x contains smoothed reference intensities
  ## n.curve$y contains smoothed i-th array intensities

  ##data <- as.numeric(approx(n.curve$y, n.curve$x, xout=data)$y)
  ##attr(data,"invariant.set") <- i.set
  ##return(data)
  return(list(n.curve=n.curve, i.set=i.set))
}







