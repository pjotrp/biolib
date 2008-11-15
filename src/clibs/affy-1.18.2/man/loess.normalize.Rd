\name{loess.normalize}
\alias{loess.normalize}

\title{Normalize arrays}
\description{
This function treats PM and MM as the raw data on each chip. It fits
loess curves to MVA plots and tries to
normalize the chips with respect to each other by forcing log ratios to
be scattered around the same constant.}
\usage{
loess.normalize(mat, subset = sample(1:(dim(mat)[2]), 5000), epsilon
                 = 10^-2, maxit = 1, log.it = TRUE, verbose = TRUE,
                 span = 2/3, family.loess = "symmetric")
}

\arguments{
  \item{mat}{a matrix with columns containing the values of the chips
    to normalize.}
  \item{subset}{a subset of the data to fit a loess to.}
  \item{epsilon}{small value used for the stopping criterion.}
  \item{maxit}{maximum number of iterations.}
  \item{log.it}{logical. If \code{TRUE} it takes the log2 of \code{mat}}
  \item{verbose}{logical. If \code{TRUE} displays current pair of chip being
    worked on.}
  \item{span}{span to be used by loess}
  \item{family.loess}{\code{"gaussian"} or \code{"symmetric"}
    as in \code{\link[modreg]{loess}}}
}
\details{
Experience shows that you only need 1-2 iterations to obtain useful
results. This function is not written in an efficient way. In order to
make it faster, loess is fit to a sample of the data which we then use to
predict the curve for all the data. By setting
\code{family.loess="gaussian"} the function is faster, but you risk
losing information on differentially expressed genes. The function
\code{\link[preprocessCore:normalize.quantiles]{normalize.quantiles}} is faster. 
}

\value{A matrix with normalized values for chips in columns.}

\seealso{\code{\link[preprocessCore:normalize.quantiles]{normalize.quantiles}}, \code{\link{maffy.normalize}},
  \code{\link{maffy.subset}}}
\author{Rafael A. Irizarry}
\keyword{smooth}
