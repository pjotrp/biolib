\name{mva.pairs}
\alias{mva.pairs}
%- Also NEED an `\alias' for EACH other topic documented here.
\title{M vs. A Matrix}
\description{
 A matrix of M vs. A plots is produced. Plots are made on the upper
 triangle and the IQR of the Ms are displayed in the lower triangle
}
\usage{
mva.pairs(x, labels=colnames(x), log.it=TRUE,span=2/3,family.loess="gaussian",
          digits=3,line.col=2,main="MVA plot",cex=2,...)
}
%- maybe also `usage' for other objects documented here.
\arguments{
  \item{x}{A matrix containing the chip data in the columns.}
  \item{labels}{the names of the variables.}
  \item{log.it}{logical. If \code{TRUE} uses log scale.}
  \item{span}{span to be used for loess fit.}
  \item{family.loess}{\code{"gaussian"} or \code{"symmetric"} as in \code{\link[modreg]{loess}}.}
  \item{digits}{number of digits to use in the display of IQR.}
  \item{line.col}{color of the loess line.}
  \item{main}{an overall title for the plot.}
  \item{cex}{size for text}
  \item{\dots}{graphical parameters can be given as arguments to \code{mva.plot}}}
\examples{
    
    x <- matrix(rnorm(4000),1000,4)
    x[,1] <- x[,1]^2
    dimnames(x) <- list(NULL,c("chip 1","chip 2","chip 3","chip 4"))
    mva.pairs(x,log=FALSE,main="example")
}

\seealso{\code{\link{pairs}}}
\keyword{hplot}


