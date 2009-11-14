\name{normalize.quantiles}
\alias{normalize.AffyBatch.quantiles}
\title{Quantile Normalization}
\description{
  Using a normalization based upon quantiles, this function
  normalizes a matrix of probe level intensities.
}
\usage{
  normalize.AffyBatch.quantiles(abatch, type=c("separate","pmonly","mmonly","together"))
}
\arguments{
  \item{abatch}{An \code{\link[affy:AffyBatch-class]{AffyBatch}}}
  \item{type}{A string specifying how the normalization should be
    applied. See details for more.}
}
\details{This method is based upon the concept of a quantile-quantile
  plot extended to n dimensions. No special allowances are made for
  outliers. If you make use of quantile normalization either through
  \code{\link{rma}} or \code{\link{expresso}}
  please cite Bolstad et al, Bioinformatics (2003).

  The type argument should be one of
  \code{"separate","pmonly","mmonly","together"} which indicates whether
  to normalize only one probe type (PM,MM) or both together or separately.
  
}

\value{
  A normalized \code{AffyBatch}.
}
\references{
  Bolstad, B (2001) \emph{Probe Level Quantile Normalization of High Density
    Oligonucleotide Array Data}. Unpublished manuscript
  \url{http://bmbolstad.com/stuff/qnorm.pdf}

  Bolstad, B. M., Irizarry R. A., Astrand, M, and Speed, T. P. (2003)
  \emph{A Comparison of Normalization Methods for High Density
    Oligonucleotide Array Data Based on Bias and Variance.}
   Bioinformatics 19(2) ,pp 185-193. \url{http://bmbolstad.com/misc/normalize/normalize.html}
  }

\author{Ben Bolstad, \email{bmbolstad.com}}

\seealso{\code{\link{normalize}}}

\keyword{manip}
