\name{bg.adjust}
\alias{bg.adjust}
\alias{bg.parameters}
%- Also NEED an `\alias' for EACH other topic documented here.
\title{Background ajustment (internal function)}
\description{
An internal function to be used by \code{\link{bg.correct.rma}}.
}
\usage{
bg.adjust(pm, n.pts = 2^14, ...)
bg.parameters(pm, n.pts = 2^14)
}
%- maybe also `usage' for other objects documented here.
\arguments{
  \item{pm}{a pm matrix}
  \item{n.pts}{number of points to use in call to \code{density}.}
  \item{...}{extra arguments to pass to bg.adjust.}
}
\details{Assumes PMs are a convolution of normal and exponentional. So we
  observe X+Y where X is backround and Y is signal. \code{bg.adjust}
    returns E[Y|X+Y, Y>0] as our backround corrected
    PM. \code{bg.parameters} provides adhoc estimates of the parameters
    of the normal and exponential distributions.}
\value{a matrix}
\seealso{\code{\link{bg.correct.rma}}}

\keyword{manip}% at least one, from doc/KEYWORDS




