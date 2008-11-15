mas5 <- function(object,normalize=TRUE,sc = 500, analysis = "absolute",...){
  res <- expresso(object,bgcorrect.method="mas",pmcorrect.method="mas",normalize=FALSE,summary.method="mas",...)
  if(normalize)
    res <- affy.scalevalue.exprSet(res,sc=sc,analysis=analysis)
  return(res)
}

mas5calls.ProbeSet <- function(object,
                               tau=0.015, alpha1=0.04, alpha2=0.06,
                               ignore.saturated=TRUE){

  if(alpha1 < 0)      {stop("alpha1 must be  > 0 "); }
  if(alpha1 > alpha2) {stop("alpha2 must be  > alpha1 "); }
  if(alpha2 > 1)      {stop("alpha2 must be  <1 "); }

  ## Saturation:
  ## shouldn't be a problem with new scanners
  ##or those that have had an engineer visit
  if(ignore.saturated) { sat <- 46000; }
  else { sat <- -1; }

  pms <- pm(object)
  mms <- mm(object)
  pns <- rep(object@id,nrow(pms))
  unique.pns <- unique(pns)

  pvals<-sapply(1:length(pms[1,]),function(x) {
    .C("DetectionPValue",as.double(pms[,x]),as.double(mms[,x]),as.character(pns),as.integer(length(mms[,x])),
       as.double(tau),as.double(sat),dpval=double(length(unique.pns)),length(unique.pns), PACKAGE="affy")$dpval;
  });
  calls <- sapply(pvals,function(y) { if(y < alpha1) { return("P") } else { if(y < alpha2) { return("M") } else { return("A") }}});

  return(list(call=calls,pval=pvals))
}

mas5calls.AffyBatch <- function(object, ids=NULL, verbose=TRUE,
                                tau=0.015, alpha1=0.04, alpha2=0.06,
                                ignore.saturated=TRUE) {
  if(alpha1 < 0)      {stop("alpha1 must be  > 0 "); }
  if(alpha1 > alpha2) {stop("alpha2 must be  > alpha1 "); }
  if(alpha2 > 1)      {stop("alpha2 must be  <1 "); }

  if(verbose) cat("Getting probe level data...\n");
  pms <-as.matrix(pm(object));
  mms <-as.matrix(mm(object));

  # Saturation:
  # shouldn't be a problem with new scanners
  ##or those that have had an engineer visit
  if(ignore.saturated) { sat <- 46000; }
  else { sat <- -1; }

  pns <- probeNames(object);
  o <- order(pns)
  pns <- pns[o]
  pms <- pms[o,,drop=FALSE]
  mms <- mms[o,,drop=FALSE]
  unique.pns <- sort(unique(pns));

  if(verbose) cat("Computing p-values\n");
  p<-sapply(1:length(pms[1,]),function(x) {
    .C("DetectionPValue",as.double(pms[,x]),as.double(mms[,x]),as.character(pns),as.integer(length(mms[,x])),
       as.double(tau),as.double(sat),dpval=double(length(unique.pns)),length(unique.pns), PACKAGE="affy")$dpval;
  });
  rownames(p) <- unique.pns;
  colnames(p) <- sampleNames(object)

  if(verbose) cat("Making P/M/A Calls\n");
  calls <- sapply(p,function(y) { if(y < alpha1) { return("P") } else { if(y < alpha2) { return("M") } else { return("A") }}});
  calls <- matrix(calls,nrow=nrow(p),ncol=ncol(p));
  colnames(calls) <- sampleNames(object)
  rownames(calls) <- rownames(p)

  if(!is.null(ids)){
    calls <- calls[ids,,drop=FALSE]
    p <- p[ids,,drop=FALSE]
  }

  eset <- new("ExpressionSet",
              phenoData=phenoData(object),
              ## featureData picked up from object
              experimentData=experimentData(object),
              annotation=annotation(object),
              exprs=calls,
              se.exprs=p
              )
  return(eset)
}


mas5.detection <- function(mat, tau=0.015, alpha1=0.04, alpha2=0.06,
                           exact.pvals=FALSE, cont.correct=FALSE) {
  ## CONSTANTS

  saturation.point <- 46000			# not a user parameter
  mat.r <- (mat[,1]-mat[,2])/(mat[,1]+mat[,2])
  ## SANITY CHECKING
  if ( !is.matrix(mat) || length(dim(mat))!=2 || dim(mat)[2]!=2 ||
      dim(mat)[1] < 1 || !is.numeric(mat) )
    stop("Invalid mat matrix.")
  if ( !is.numeric(tau) )
    stop("Invalid tau.")
  if ( !is.numeric(alpha1) || !is.numeric(alpha2) ||
      alpha1 <= 0 || alpha1 >= alpha2 || alpha2 >= 0.5 )
    stop("Invalid alpha1 or alpha2.")
  if ( !is.logical(exact.pvals) )
    stop("Invalid exact.pvals.")
  if ( !is.logical(cont.correct) )
        stop("Invalid cont.correct.")

  ## DEALING WITH SATURATION; COMPUTING THE P-VALUE
  ## According to the Bioinformatics paper:
  ## * If all MM's are saturated, then call present
  ## * Otherwise discard pairs with a saturated MM
  ## According to the Affymetrix whitepaper:
  ## * If all probe-pairs are saturated, then call present with pval=0
  ## * If an MM is saturated, then we discard the pair
  ## * If a PM and MM are within tau of each other, we discard the pair
  ## So we're going with:
  ## * If all MM's are saturated, set pval=0 and don't use Wilcoxon
  ## * Discard probe-pairs when MM is saturated or the PM,MM are within tau
  ##   of each other
  ## * Compute the p-value using Wilcoxon's signed rank test on the retained
  ##   probe-pairs
  is.mm.saturated <- function(probe.pair, saturation.point)
        probe.pair[2] >= saturation.point
  is.retained <- function(probe.pair, saturation.point, tau)
    !(is.mm.saturated(probe.pair,saturation.point) ||
      abs(diff(probe.pair)) <= tau)
  if ( all(apply(mat,1,is.mm.saturated,saturation.point)) )
    pval <- 0
  else {
    retained <- apply(mat, 1, is.retained, saturation.point, tau)
    pval <- wilcox.test(mat.r[retained],
                        alternative="greater", mu=tau, paired=FALSE,
                        exact=exact.pvals, correct=cont.correct,
                        conf.int=FALSE)$p.value
  }

  ## DETECTION CALL
  if ( pval < 0 || pval > 1 )
    warning("Computed an unusual p-value outside the range [0,1].")
  if ( pval < alpha1 )
    call <- "P"
  else if ( pval < alpha2 )
        call <- "M"
  else
        call <- "A"

  ## DONE
  return(list(pval=pval, call=call))
}

