\name{normalize.loess}
\alias{normalize.loess}
\alias{normalize.AffyBatch.loess}
\title{Scale microarray data}
\description{Normalizes arrays using loess.}
\usage{
normalize.loess(mat, subset = sample(1:(dim(mat)[1]), min(c(5000,
                 nrow(mat)))), epsilon = 10^-2, maxit = 1, log.it =
                 TRUE, verbose = TRUE, span = 2/3, family.loess =
                 "symmetric")
normalize.AffyBatch.loess(abatch,type=c("together","pmonly","mmonly","separate"), ...)
}
\arguments{
  \item{mat}{a matrix with columns containing the values of the chips
    to normalize.}
  \item{abatch}{an \code{\link[affy:AffyBatch-class]{AffyBatch}} object.}
  \item{subset}{a subset of the data to fit a loess to.}
  \item{epsilon}{a tolerance value (supposed to be a small value - used
    as a stopping criterium).}
  \item{maxit}{maximum number of iterations.}
  \item{log.it}{logical. If \code{TRUE} it takes the log2 of \code{mat}}
  \item{verbose}{logical. If \code{TRUE} displays current pair of chip being
    worked on.}
  \item{span}{parameter to be passed the function \code{\link[stats]{loess}}}
  \item{family.loess}{parameter to be passed the function
    \code{\link[stats]{loess}}. \code{"gaussian"} or \code{"symmetric"}
    are acceptable values for this parameter.}
  \item{type}{A string specifying how the normalization should be
    applied. See details for more.}
  \item{...}{any of the options of normalize.loess you would like to
    modify (described above).}
}
\details{
  The type arguement should be one of
  \code{"separate","pmonly","mmonly","together"} which indicates whether
  to normalize only one probe type (PM,MM) or both together or separately.
}
\seealso{
  \code{\link{normalize}}
}
\examples{
     #require(affy)
     #data(Dilution)
     #x <- pm(Dilution[,1:3])
     #mva.pairs(x)
     #x <- normalize.loess(x,subset=1:nrow(x))
     #mva.pairs(x)
}
\keyword{smooth}


