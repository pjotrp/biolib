\name{barplot.ProbeSet}
\alias{barplot.ProbeSet}
\title{show a ProbeSet as barplots}
\description{
  displays the probe intensities in a ProbeSet as a barplots
}
\usage{
\method{barplot}{ProbeSet}(height, xlab = "Probe pair", ylab = "Intensity", main =
NA, col.pm = "red", col.mm = "blue", beside = TRUE, names.arg = "pp",
ask = TRUE, scale, ...)
}
%- maybe also `usage' for other objects documented here.
\arguments{
  \item{height}{an object of class \code{ProbeSet} }
  \item{xlab}{ label for x axis }
  \item{ylab}{ label for y axis }
  \item{main}{ main label for the figure }
  \item{col.pm}{ color for the `pm' intensities }
  \item{col.mm}{ color for the `mm' intensities }
  \item{beside}{ bars beside eachothers or not }
  \item{names.arg}{  }
  \item{ask}{ ask before ploting the next barplot }
  \item{scale}{ put all the barplot to the same scale }
  \item{\dots}{ extra parameters to be passed to \code{\link{barplot}} }
}
\examples{
data(affybatch.example)
gn <- geneNames(affybatch.example)
pps <- probeset(affybatch.example, gn[1])[[1]]

barplot.ProbeSet(pps)
}
\keyword{hplot}

