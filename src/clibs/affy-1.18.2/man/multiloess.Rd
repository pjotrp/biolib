\name{multiloess}
\alias{multiloess}
\title{Local Polynomial Regression Fitting}
\description{A modified version of of loess. 
Perform loess for every column of Y, but with the robust weights calculated using all columns}
\usage{
multiloess(formula, data=NULL, weights, subset, na.action, model = FALSE,
	 span = 0.75, enp.target, degree = 2,
	 normalize = TRUE,
	 family = c("gaussian", "symmetric"),
	 method = c("loess", "model.frame"),
	 control = loess.control(...), ...)
}
%- maybe also `usage' for other objects documented here.
\arguments{
See \code{\link[modreg]{loess}}.
}
\details{
Please refer to \code{\link[modreg]{loess}}.
}
\value{
  See \code{\link[modreg]{loess}}.
 }
\references{Astrand, M. (2001) \url{http://www.math.chalmers.se/~magnusaa/maffy/}}
\author{Magnus Astrand}
\seealso{ \code{\link{loess}}}
\keyword{internal}


