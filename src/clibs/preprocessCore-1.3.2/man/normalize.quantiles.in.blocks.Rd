\name{normalize.quantiles.in.blocks}
\alias{normalize.quantiles.in.blocks}
\title{Quantile Normalization carried out separately within blocks of rows}
\description{
  Using a normalization based upon quantiles this function
  normalizes the columns of a matrix such that different subsets of rows
  get normalized together.
}
\usage{
  normalize.quantiles.in.blocks(x,blocks,copy=TRUE)
}
\arguments{
  \item{x}{A matrix of intensities where each column corresponds to a
    chip and each row is a probe.}
  \item{copy}{Make a copy of matrix before normalizing. Usually safer to
    work with a copy}
  \item{blocks}{A vector giving block membership for each each row}
}
\details{This method is based upon the concept of a quantile-quantile
  plot extended to n dimensions. No special allowances are made for
  outliers. If you make use of quantile normalization either through
  \code{\link[affy]{rma}} or \code{\link[affy]{expresso}}
  please cite Bolstad et al, Bioinformatics (2003).

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


 \examples{
   ### setup the data
   blocks <- c(rep(1,5),rep(2,5),rep(3,5))
   par(mfrow=c(3,2))
   x <- matrix(c(rexp(5,0.05),rnorm(5),rnorm(5,10)))
   boxplot(x ~ blocks)
   y <- matrix(c(-rexp(5,0.05),rnorm(5,10),rnorm(5)))
   boxplot(y ~ blocks)
   pre.norm <- cbind(x,y)

   ### the in.blocks version
   post.norm <- normalize.quantiles.in.blocks(pre.norm,blocks)
   boxplot(post.norm[,1] ~ blocks)
   boxplot(post.norm[,2] ~ blocks)

   ### the usual version
   post.norm  <- normalize.quantiles(pre.norm)
   boxplot(post.norm[,1] ~ blocks)
   boxplot(post.norm[,2] ~ blocks)
 }


 
\author{Ben Bolstad, \email{bmb@bmbolstad.com}}

\seealso{\code{\link[affy]{normalize}}}

\keyword{manip}
