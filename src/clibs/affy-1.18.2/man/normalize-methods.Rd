\name{normalize-methods}
\title{Normalize Affymetrix Probe Level Data - methods}
\docType{methods}
\alias{normalize.AffyBatch}
\alias{normalize.methods}
\alias{normalize.AffyBatch.methods}
\alias{normalize,AffyBatch-method}
\alias{normalize.methods,AffyBatch-method}

\description{
  Method for normalizing Affymetrix Probe Level Data
}
\usage{
normalize.methods(object)
}
\arguments{
  \item{object}{An \code{\link[affy:AffyBatch-class]{AffyBatch}}.}
%  \item{...}{Optional arguments to be passed along. See details.}
}
\details{

  If \code{object} is an
  \code{\link[affy:AffyBatch-class]{AffyBatch}} then
  \code{normalize(object)} returns an
  \code{\link[affy:AffyBatch-class]{AffyBatch}} with the intensities
  normalized using the methodology specified by
  \code{getOption("BioC")$affy$normalize.method}. The affy package
  default is \code{quantiles}.

  Other methodologies can be used by specifying them with the
  \code{method} argument. For example to use the invariant set
  methodology described by Li and Wong (2001) one would type:
  \code{normalize(object, method="invariantset")}.

  Further arguments passed by \code{...}, apart from \code{method},  are
  passed along to the 
  function responsible for the methodology defined by the \code{method}
  argument. 
  
  A character vector of \emph{nicknames} for the 
  methodologies available is returned by
  \code{normalize.methods(object))}, where \code{object} 
  is an  \code{\link[affy:AffyBatch-class]{AffyBatch}}, or simply by
  typing \code{normalize.AffyBatch.methods}. If the nickname of a method
  is called "loess", the help page for that 
  specific methodology can
  be accessed by typing \code{?normalize.loess}. 

  For more on the normalization methodologies currently implemented
  please refer to the vignette `Custom Processing Methods'.

  To add your own normalization procedures please
  refer to the customMethods vignette.

}
\seealso{
  \code{\link{AffyBatch-class}}, \code{\link{normalize}}.
}
\examples{
data(affybatch.example)
normalize.methods(affybatch.example)
}
\keyword{manip}



