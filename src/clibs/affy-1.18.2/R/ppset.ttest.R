ppset.ttest <- function(ppset, covariate, pmcorrect.fun = pmcorrect.pmonly, ...) {
  probes <- do.call("pmcorrect.fun", list(ppset))
  my.ttest <- function(x) {
    y <- split(x, get(covariate))
    t.test(y[[1]], y[[2]])$p.value
  }
  r <- apply(probes, 1, my.ttest)
  return(r)
}

