\name{normalize.quantiles.target}
\alias{normalize.quantiles.use.target}
\alias{normalize.quantiles.determine.target}
\title{Quantile Normalization using a specified target distribution vector}
\description{
  Using a normalization based upon quantiles, these function
  normalizes the columns of a matrix based upon a specified
  normalization distribution
}
\usage{
  normalize.quantiles.use.target(x,target,copy=TRUE)
  normalize.quantiles.determine.target(x,target.length=NULL)
}
\arguments{
  \item{x}{A matrix of intensities where each column corresponds to a
    chip and each row is a probe.}
  \item{copy}{Make a copy of matrix before normalizing. Usually safer to
    work with a copy}
  \item{target}{A vector containing datapoints from the distribution to
    be normalized to}
  \item{target.length}{number of datapoints to return in target
    distribution vector. If \code{NULL} then this will be taken to be
    equal to the number of rows in the matrix.} 
}
\details{This method is based upon the concept of a quantile-quantile
  plot extended to n dimensions. No special allowances are made for
  outliers. If you make use of quantile normalization either through
  \code{\link[affy]{rma}} or \code{\link[affy]{expresso}}
  please cite Bolstad et al, Bioinformatics (2003).


  These functions will handle missing data (ie NA values), based on the
  assumption that the data is missing at random.
  
}

\value{
  From \code{normalize.quantiles.use.target} a normalized \code{matrix}.
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

\author{Ben Bolstad, \email{bmb@bmbolstad.com}}

\seealso{\code{\link[affy]{normalize}}}

\keyword{manip}
