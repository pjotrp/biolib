plot.ProbeSet <- function(x, which=c("pm", "mm"), xlab="probes", type="l", ylim=NULL, ...) {

  which <- match.arg(which)
  if (which == "pm")
    f <- getMethod("pm", "ProbeSet")
  else
    f <- getMethod("mm", "ProbeSet")
  
  if (is.null(ylim))
    ylim = range(c(f(x)), na.rm=TRUE)
  
  if (is.na(xlab))
    xlab="probes"
  
  matplot(f(x), xlab=xlab, type=type, ylim=ylim, ...)  
}
