\name{normalize.constant}
\alias{normalize.constant}
\alias{normalize.AffyBatch.constant}
\title{Scale probe intensities}
\description{
  Scale array intensities in a \code{\link[affy:AffyBatch-class]{AffyBatch}}.
}
\usage{
normalize.AffyBatch.constant(abatch, refindex=1, FUN=mean, na.rm=TRUE)
normalize.constant(x, refconstant, FUN=mean, na.rm=TRUE)
}
\arguments{
  \item{abatch}{ an instance of the \code{\link{AffyBatch-class}}.}
  \item{x}{a vector of intensities on a chip (to normalize to the reference).}
  \item{refindex}{the index of the array used as a reference.}
  \item{refconstant}{the constant used as a reference}
  \item{FUN}{A function generating a value from the intensities on an
    array. Typically \code{mean} or \code{median}.}
  \item{na.rm}{Paramater passed to the function FUN.}
}
\value{
  %A \code{\link[Biobase]{container-class}} of normalized objects.
  An \code{\link[affy:AffyBatch-class]{AffyBatch}} with an attribute "constant"
  holding the value of the factor used for scaling.
}
\author{
  L. Gautier <laurent@cbs.dtu.dk>
}
\seealso{
  \code{\link[affy:AffyBatch-class]{AffyBatch}}
}
\keyword{manip}
