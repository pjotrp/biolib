\name{tukey.biweight}
\alias{tukey.biweight}

\title{ One-step Tukey's biweight}
\description{
  One-step Tukey's biweight on a matrix
}
\usage{
tukey.biweight(x, c = 5, epsilon = 1e-04)
}
\arguments{
  \item{x}{ a matrix }
  \item{c}{ tuning constant (see details)}
  \item{epsilon}{ fuzz value to avoid division by zero (see details)}
}
\details{
  The details can be found in the given reference.
}
\value{
  a vector of values (one value per column in the input matrix).
}
\references{ Statistical Algorithms Description Document, 2002, Affymetrix. }

\seealso{
  \code{\link{pmcorrect.mas}} and \code{\link{generateExprVal.method.mas}} 
}
\keyword{ manip }

