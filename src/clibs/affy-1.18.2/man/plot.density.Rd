%\name{matdensity}
\name{plotDensity}
%\alias{matdensity}
\alias{plotDensity}
\alias{plotDensity.AffyBatch}
%- Also NEED an `\alias' for EACH other topic documented here.
\title{Plot Densities}
\description{
Plots the non-parametric density estimates using values contained in the
columns of a matrix.
}
\usage{
%matdensity(mat, ylab = "density", xlab="x", type="l", ...)

plotDensity(mat, ylab = "density", xlab="x", type="l", col=1:6,
            na.rm = TRUE, ...)

plotDensity.AffyBatch(x, col = 1:6, log = TRUE,
                      which=c("pm","mm","both"),
                      ylab = "density",
                      xlab = NULL, ...)

}
%- maybe also `usage' for other objects documented here.
\arguments{
  \item{mat}{A matrix containing the values to make densities in the columns.}
  \item{x}{A object of clase \code{\link[affy:AffyBatch-class]{AffyBatch}}}
  \item{log}{logical value. If \code{TRUE} the log of the intensities in
    the \code{AffyBatch} are plotted.}
  \item{which}{should a histogram of the PMs, MMs, or both be made?}
  \item{col}{The colors to use fot the different arrays}
  \item{ylab}{a title for the y axis.}
  \item{xlab}{ a title for the x axis.}
  \item{type}{ type for the plot.}
  \item{na.rm}{ handling of \code{NA} values.}
  \item{\dots}{graphical parameters can be given as arguments to \code{\link{plot}}}
}

\details{

  The list returned can be convenient for plotting large input matrices
  with different colors/line types schemes
  (the computation of the densities can take some time).

  To match other functions in base R, this function should probably be
  called \code{matdensity}, as it is sharing similarities with
  \code{matplot} and \code{matlines}. 
}

\value{
  It returns invisibly a list of two matrices `x' and `y'.
}
\author{Ben Bolstad and Laurent Gautier}

\examples{
data(affybatch.example)

m <- exprs(affybatch.example)

plotDensity(exprs(affybatch.example))

}
\keyword{hplot}% at least one, from doc/KEYWORDS






