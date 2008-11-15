\name{normalize.quantiles}
\alias{normalize.quantiles}
\title{Quantile Normalization}
\description{
  Using a normalization based upon quantiles, this function
  normalizes a matrix of probe level intensities.
}
\usage{
  normalize.quantiles(x,copy=TRUE)
}
\arguments{
  \item{x}{A matrix of intensities where each column corresponds to a
    chip and each row is a probe.}
  \item{copy}{Make a copy of matrix before normalizing. Usually safer to
    work with a copy, but in certain situations not making a copy of the
    matrix, but instead normalizing it in place will be more memory friendly.}
}
\details{This method is based upon the concept of a quantile-quantile
  plot extended to n dimensions. No special allowances are made for
  outliers. If you make use of quantile normalization 
  please cite Bolstad et al, Bioinformatics (2003).

  This functions will handle missing data (ie NA values), based on the
  assumption that the data is missing at random.

  Note that the current implementation optimizes for better memory usage
  at the cost of some additional run-time.

}

\value{
  A normalized \code{matrix}.
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

\seealso{\code{\link{normalize.quantiles.robust}}}

\keyword{manip}
