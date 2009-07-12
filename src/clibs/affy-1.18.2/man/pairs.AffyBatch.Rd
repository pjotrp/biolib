\name{pairs.AffyBatch}
\alias{pairs.AffyBatch}
\title{plot intensities using 'pairs'}
\description{
  Plot intensities using the function 'pairs'
}
\usage{
\method{pairs}{AffyBatch}(x, panel=points, ..., transfo=I, main=NULL, oma=NULL,
                  font.main = par("font.main"),
                  cex.main = par("cex.main"), cex.labels = NULL, 
                  lower.panel=panel, upper.panel=NULL, diag.panel=NULL,
                  font.labels = 1, row1attop = TRUE, gap = 1)
}
\arguments{
  \item{x}{ an \code{\link[affy:AffyBatch-class]{AffyBatch}} object }
  \item{panel}{ a function to produce a plot (see \code{\link{pairs}}) }
  \item{...}{ extra parameters for the 'panel' function}
  \item{transfo}{ a function to transform the intensity values before
    generating the plot. 'log' and 'log2' are popular choices. }
  \item{main}{title for the plot}
  \item{oma}{see 'oma' in \code{\link{par}}.}
  \item{font.main}{see \code{\link{pairs}}}
  \item{cex.main}{see \code{\link{pairs}}}
  \item{cex.labels}{see \code{\link{pairs}}}
  \item{lower.panel}{a function to produce the plots in the lower
triangle (see \code{\link{pairs}}).}
  \item{upper.panel}{a function to produce the plots in the upper
triangle (see \code{\link{pairs}}).}
  \item{diag.panel}{a function to produce the plots in the diagonal (see \code{\link{pairs}}).}
  \item{font.labels}{see \code{\link{pairs}}}
  \item{row1attop}{see \code{\link{pairs}}}
  \item{gap}{see \code{\link{pairs}}}
}
\details{
  Plots with several chips can represent zillions of points. They require
a lot of memory and can be very slow to be displayed. You may want to
try to split of the plots, or to plot them in a device like 'png' or
'jpeg'. 
}
\keyword{hplot}


