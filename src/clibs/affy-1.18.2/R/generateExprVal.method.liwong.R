generateExprVal.method.liwong <- function(probes, ...) {
  probes <- t(probes)
  if (ncol(probes) == 1) {
    warning("method liwong unsuitable when only one probe pair")
    list(exprs=as.vector(probes),se.exprs=rep(NA,length(probes)))
  }
  else {
    tmp <- fit.li.wong(probes, ...)
    list(exprs=tmp$theta,se.exprs=tmp$sigma.theta)
  }
}
