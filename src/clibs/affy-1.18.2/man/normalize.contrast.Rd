\name{normalize.contrasts}
\alias{normalize.contrasts}
\alias{normalize.AffyBatch.contrasts}
\title{Normalize intensities using the contrasts method}
\description{
  Scale chip objects in an \code{\link{AffyBatch-class}}.
}
\usage{
%normalize.contrast() ## currenlt maffy.normalize
normalize.AffyBatch.contrasts(abatch,span=2/3,choose.subset=TRUE,
                              subset.size=5000,verbose=TRUE,
                              family="symmetric",type=c("together","pmonly","mmonly","separate"))
}
\arguments{
  \item{abatch}{ an \code{\link{AffyBatch-class}}}
  \item{span}{parameter to be passed to the function \code{\link[modreg]{loess}}.}
  \item{choose.subset}{}
  \item{subset.size}{}
  \item{verbose}{verbosity flag}
  \item{family}{parameter to be passed to the function \code{\link[modreg]{loess}}.}
  \item{type}{A string specifying how the normalization should be
    applied.}

}
\value{
  An object of the same class as the one passed.
}
\seealso{
  \code{\link{maffy.normalize}}
  }
\keyword{manip}

