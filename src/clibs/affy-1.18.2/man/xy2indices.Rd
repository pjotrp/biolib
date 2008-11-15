\name{xy2indices}
\alias{xy2indices}
\alias{indices2xy}
\title{ Functions to convert indices to x/y (and reverse)}
\description{
  Functions to convert indices to x/y (and reverse)
}
\usage{
xy2indices(x, y, nr = NULL, cel = NULL, abatch = NULL, cdf = NULL, xy.offset = NULL)
indices2xy(i, nr = NULL, cel = NULL, abatch = NULL, cdf = NULL, xy.offset = NULL)
}
\arguments{
  \item{x}{ \code{X} position for the probes }
  \item{y}{ \code{Y} position for the probes }
  \item{i}{ indices in the \code{AffyBatch} for the probes }
  \item{nr}{ total number of \code{Xs} on the chip }
  \item{cel}{ a corresponding object of class \code{\link[affy:Cel-class]{Cel}} }
  \item{abatch}{ a corresponding object of class
    \code{\link[affy:AffyBatch-class]{AffyBatch}} }
  \item{cdf}{ character - the name of the corresponding cdf package}
  \item{xy.offset}{an eventual offset for the XY coordinates. See Details}
}
\details{
  The probes intensities for given probe set ids are extracted from an
  \code{AffyBatch} object using the indices stored in the corresponding
  \code{cdfenv}.

  The parameter \code{xy.offset} is there for compatibility.
  For historical reasons, the xy-coordinates for the features
  on Affymetrix chips were decided to start at 1 (one) rather than 0
  (zero). One can set the offset to 1 or to 0. Unless the you \_really\_
  know what you are doing, it is advisable to let it at the default
  value \code{NULL}. This way the package-wide option code{xy.offset} is
  always used.
}
\value{
  A vector of indices or a two-columns matrix of Xs and Ys. 
}
\author{ L. }
\section{Warning}{ Even if one really knows what is going on, playing with the
  parameter \code{xy.offset} could be risky. Changing the package-wide
  option \code{xy.offset} appears much more sane.}
\seealso{\code{\link{indexProbes}}}
\examples{
data(affybatch.example)

pm.i <- indexProbes(affybatch.example, which="pm", genenames="AFFX-BioC-5_at")[[1]]
mm.i <- indexProbes(affybatch.example, which="mm", genenames="AFFX-BioC-5_at")[[1]]

pm.i.xy <- indices2xy(pm.i, abatch = affybatch.example)
mm.i.xy <- indices2xy(mm.i, abatch = affybatch.example)

image(affybatch.example[1], transfo=log2)
## plot the pm in red
plotLocation(pm.i.xy, col="red")
plotLocation(mm.i.xy, col="blue")


}
\keyword{ manip }
