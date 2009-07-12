ppsetApply <- function(abatch, FUN, genenames=NULL, ...) {

    if (! is(abatch, "AffyBatch"))
        stop("abatch must be inheriting from class AffyBatch")

    if (! is(FUN, "function"))
        stop("FUN must be a function")

  cdfenv <- getCdfInfo(abatch)

  if (is.null(genenames))
    genenames <- ls(cdfenv)

  ##
  e1 <- new.env(parent = environment(FUN))
  multiassign(names(pData(abatch)), pData(abatch), env = e1)
  environment(FUN) <- e1

  ppset <- new("ProbeSet", pm=matrix(), mm=matrix())

  r <- vector("list", length=length(genenames))
  names(r) <- genenames

  for (i in seq(along=genenames)) {
    ## use mget to get NA when genenames[i] not found
    probes.i <- mget(genenames[i], envir = cdfenv, ifnotfound = NA)[[1]]
    if (all(is.na(probes.i)))
      next
    ppset@pm <- intensity(abatch)[probes.i[, 1], , drop=FALSE]
    ppset@mm <- intensity(abatch)[probes.i[, 2], , drop=FALSE]
    ppset@id <- genenames[i]
    r[[i]] <- FUN(ppset, ...)
  }

  return(r)
}

