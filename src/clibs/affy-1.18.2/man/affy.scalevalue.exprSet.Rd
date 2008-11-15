%%%THIS FUNCTION SHOULD BE In BIOBASE or SOMEWHERE ELSE... NEXT RELEASE
%% LG: In such a case, I assume the long awaited agreement about
%% normalization methods will be here and all the normalization methods
%% will be stored together
\name{affy.scalevalue.exprSet}
\alias{affy.scalevalue.exprSet}
\title{Scale normalization for expreSets}
\description{
  Normalizes expression values using the method described in the
  Affymetrix user manual.
}
\usage{
affy.scalevalue.exprSet(eset, sc = 500, analysis="absolute")
}
\arguments{
  \item{eset}{An \code{\link[Biobase:class.ExpressionSet]{ExpressionSet}} object.}
  \item{sc}{Value at which all arrays will be scaled to.}
  \item{analysis}{Should we do absolute or comparison analysis, although
  "comparison" is still not implemented.}
}
\details{
  This is function was implemented from the Affymetrix technical
  documentation for MAS 5.0. It can be downloaded from the website of
  the company. Please refer to this document for details.
}
\author{Laurent}
\value{
  A normalized \code{\link[Biobase:class.ExpressionSet]{ExpressionSet}}}
\keyword{manip}
