## Currently, the input is a 2 matrices a pm and a mm

##avdiff is more like median than mean, it would be nice to actually have
##avfif
##added typical se of the mean as returned se
generateExprVal.method.avgdiff <- function(probes, ...) {
  list(exprs=apply(probes, 2, median),se.exprs=apply(probes,2,sd)/sqrt(nrow(probes)))
}
