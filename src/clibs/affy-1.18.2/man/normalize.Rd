\name{normalize}
\alias{normalize}
\title{Normalize - generic}
\description{
A generic function which normalizes microarray data.
Normalization is intended to remove from the intensity measures any
systematic trends which arise from the microarray technology rather than
from differences between the probes or between the target RNA samples
hybridized to the arrays. 
}
\usage{
normalize(object, ...)
}
\arguments{
  \item{object}{a data object containing microarray data}
  \item{...}{any other arguments}
}
\seealso{
  Type \code{showMethods("normalize")} at the R prompt to see what
  methods are available. Help on individual methods is generally available
  as \code{normalize}.<class> where <class> is the class of the data
  object. For example, for the main class in the \code{affy} package use \code{?normalize.AffyBatch}.

  Other Bioconductor packages include some related generic functions:
  \code{\link[limma]{normalizeWithinArrays}}, and 
  \code{\link[limma]{normalizeBetweenArrays}}, in the LIMMA package, and 
  \code{\link[marrayNorm]{maNorm}} in the marrayNorm package.
}
\keyword{models}

