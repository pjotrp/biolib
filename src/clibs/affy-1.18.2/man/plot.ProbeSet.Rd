\name{plot.ProbeSet}
\alias{plot.ProbeSet}
\title{plot a probe set}
\description{
  Plot intensities by probe set.
}
\usage{
\method{plot}{ProbeSet}(x, which=c("pm", "mm"), xlab = "probes", type = "l", ylim = NULL, ...)
}
\arguments{
  \item{x}{ a \code{ProbeSet} }
  \item{which}{ get the PM or the MM}
  \item{xlab}{ label on x-axis }
  \item{type}{ plot type }
  \item{ylim}{ range of the y-axis }
  \item{\dots}{ optional arguments to be passed to \code{matplot} }
}
\value{
  This function is only used for its (graphical) side-effect.
}

\seealso{\code{\link[affy:ProbeSet-class]{ProbeSet}}}

\examples{
data(SpikeIn)
plot(SpikeIn)
}
\keyword{ hplot }% at least one, from doc/KEYWORDS
