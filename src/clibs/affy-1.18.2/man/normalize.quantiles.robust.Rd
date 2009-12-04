\name{normalize.quantiles.robust}
\alias{normalize.AffyBatch.quantiles.robust}
\title{Robust Quantile Normalization}
\description{Using a normalization based upon quantiles, this function
  normalizes a matrix of probe level intensities. Allows weighting of chips}
\usage{
    normalize.AffyBatch.quantiles.robust(abatch,
type=c("separate","pmonly","mmonly","together"),
weights=NULL,remove.extreme=c("variance","mean","both","none"),n.remove=1,use.median=FALSE,use.log2=FALSE)

}

\arguments{
  \item{abatch}{An \code{\link[affy:AffyBatch-class]{AffyBatch}}}
  \item{type}{A string specifying how the normalization should be
    applied. See details for more.}
  \item{weights}{A vector of weights, one for each chip}
  \item{remove.extreme}{If weights is null, then this will be used for
  determining which chips to remove from the calculation of the
  normalization distribution, See details for more info}
  \item{n.remove}{number of chips to remove}
  \item{use.median}{if TRUE use the median to compute normalization
    chip, otherwise uses a weighted mean}
  \item{use.log2}{work on log2 scale. This means we will be using the
    geometric mean rather than ordinary mean}
}
\details{This method is based upon the concept of a quantile-quantile 
  plot extended to n dimensions. Note that the matrix is of intensities
  not log intensities. The function performs better with raw
  intensities.
  
  Choosing \bold{variance} will remove chips with variances much higher
  or lower than the other chips, \bold{mean} removes chips with the mean
  most different from all the other means, \bold{both} removes first
  extreme variance and then an extreme mean. The option \bold{none} does
  not remove any chips, but will assign equal weights to all chips.
 
  The type argument should be one of
  \code{"separate","pmonly","mmonly","together"} which indicates whether
  to normalize only one probe type (PM,MM) or both together or separately.
 
}
\note{This function is still experimental.}
\value{a matrix of normalized intensites}
\author{Ben Bolstad, \email{bmb@bmbolstad.com}}

\seealso{\code{\link{normalize}}, \code{\link[preprocessCore:normalize.quantiles]{normalize.quantiles}}}
\keyword{manip}




