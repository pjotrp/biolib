\name{MAplot}
\alias{ma.plot}
\alias{Mbox}
\alias{MAplot}
\alias{Mbox,AffyBatch-method}
\alias{MAplot,AffyBatch-method}

\title{Relative M vs. A plots}
\description{
  Create boxplots of M or M vs A plots. Where M is determined relative
  to a specified chip or to a pseudo-median reference chip.
}
\usage{
MAplot(object,...)
Mbox(object,...)
ma.plot(A, M, subset = sample(1:length(M), min(c(10000, length(M)))),
show.statistics=TRUE, span=2/3, family.loess="gaussian", cex = 2,plot.method=c("normal","smoothScatter","add"),add.loess = TRUE,lwd = 1, lty = 1, loess.col = "red",...)
}

\arguments{
  \item{object}{An \code{\link{AffyBatch-class}}}
  \item{...}{Additional parameters for the routine}
  \item{A}{A vector to plot along the horizonal axis}
  \item{M}{A vector to plot along vertical axis}
  \item{subset}{A set of indices to use when drawing the loess curve}
  \item{show.statistics}{If true some summary statistics of the M values
    are drawn}
  \item{span}{span to be used for loess fit.}
  \item{family.loess}{\code{"guassian"} or \code{"symmetric"} as in
    \code{\link[modreg]{loess}}.}
  \item{cex}{Size of text when writing summary statistics on plot}
  \item{plot.method}{a string specifying how the plot is to be
    drawn. \code{"normal"} plots points, \code{"smoothScatter"} uses the
  \code{\link[geneplotter]{smoothScatter}} function. Specifying
  \code{"add"} means that the MAplot should be added to the current
  plot}
\item{add.loess}{add a loess line to the plot}
\item{lwd}{width of loess line}
\item{lty}{line type for loess line}
\item{loess.col}{color for loess line}


}
\examples{
   data(affybatch.example)
   MAplot(affybatch.example)
   Mbox(affybatch.example)
}

\seealso{\code{\link{mva.pairs}}}
\keyword{hplot}
