\name{rma}
\alias{rma}
\title{Robust Multi-Array Average expression measure}
\description{
  This function converts an \code{\link[affy:AffyBatch-class]{AffyBatch}} into an
  \code{\link[Biobase:class.ExpressionSet]{ExpressionSet}} using
  the robust multi-array average (RMA) expression measure.
}
\usage{
rma(object,subset=NULL, verbose=TRUE, destructive = TRUE,normalize=TRUE,background=TRUE,bgversion=2,...)
}
%- maybe also `usage' for other objects documented here.
\arguments{
  \item{object}{an \code{\link[affy:AffyBatch-class]{AffyBatch}}}
  \item{subset}{a character vector with the the names of the probesets
    to be used in expression calculation.}
  \item{verbose}{logical value. If \code{TRUE} it writes out some
    messages indicating progress. If \code{FALSE} nothing should be printed.}
  \item{destructive}{logical value. If \code{TRUE} works on the PM matrix in place as much as possible, good for large datasets.}
  \item{normalize}{logical value. If \code{TRUE} normalize data using
    quantile normalization}
  \item{background}{logical value. If \code{TRUE} background correct
    using RMA background correction}
  \item{bgversion}{integer value indicating which RMA background to use
1: use background similar to pure R rma background given in affy version 1.0 - 1.0.2
2: use background similar to pure R rma background given in affy version 1.1 and above}
  \item{\dots}{further arguments to be passed (not currently implemented - stub for future use)}
}
\details{
This function computes the RMA (Robust Multichip Average) expression measure described in Irizarry et al
Biostatistics (2003).

Note that this expression measure is given to you in log base 2
scale. This differs from most of the other expression measure methods.

Please note that the default background adjustment method was changed during the lead up
to the bioconductor 1.2 release. This means that this function and
\code{\link{expresso}} should give results that directly agree.

}
\value{
An \code{\link[Biobase:class.ExpressionSet]{ExpressionSet}}
}

\author{Ben Bolstad \email{bmb@bmbolstad.com}}

\references{
  Rafael. A. Irizarry, Benjamin M. Bolstad, Francois Collin, Leslie M. Cope, Bridget Hobbs and Terence P. Speed (2003), Summaries of Affymetrix GeneChip probe level data Nucleic Acids Research 31(4):e15

  Bolstad, B.M., Irizarry R. A., Astrand M., and Speed, T.P. (2003), A Comparison of Normalization Methods for High Density Oligonucleotide Array Data Based on Bias and Variance. Bioinformatics 19(2):185-193

  Irizarry, RA, Hobbs, B, Collin, F, Beazer-Barclay, YD, Antonellis, KJ, Scherf, U, Speed, TP (2003) Exploration, Normalization, and Summaries of High Density Oligonucleotide Array Probe Level Data. Biostatistics .Vol. 4, Number 2: 249-264 
}
\seealso{\code{\link{expresso}} }

\examples{
data(affybatch.example)
eset <- rma(affybatch.example)
}
\keyword{manip}

