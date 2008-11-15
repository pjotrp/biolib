\name{simplemultiLoess}
\alias{simplemultiLoess}
\title{Internal function for multiloess}
\description{A modified version of of simpleLoess. 
Perform loess for every column of Y, but with the robust weights calculated using all columns}
\usage{
simplemultiLoess(y, x, weights, span = 0.75, degree = 2,
	   normalize = TRUE,
	   statistics = "approximate", surface = "interpolate",
	   cell = 0.2, iterations = 1, trace.hat = "exact")
}
%- maybe also `usage' for other objects documented here.
\arguments{
  See  \code{\link[modreg]{loess}}.
}
\details{
  Please refer to  \code{\link[modreg]{loess}}.
}
\value{
  See  \code{\link[modreg]{loess}}.
}
\references{Astrand, M. (2001) \url{http://www.math.chalmers.se/~magnusaa/maffy/}}
\author{Magnus Astrand}
\seealso{ \code{\link[modreg]{loess}}}
\keyword{internal}


