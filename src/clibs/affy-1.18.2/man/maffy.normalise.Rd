\name{maffy.normalize}
\alias{maffy.normalize}
\alias{normalize.contrast}
\title{Normalize Itensities}
\description{Normalizes feauture intensities from
  \code{\link[affy:AffyBatch-class]{AffyBatch}}s}
\usage{
maffy.normalize(data,subset,verbose=FALSE,span=0.25,family="symmetric",log.it=TRUE)}
%- maybe also `usage' for other objects documented here.
\arguments{
  \item{data}{an matrix of intensities.}
  \item{subset}{a vector of indexes describing which probes to use for normalising.}
  \item{verbose}{logical value.}
  \item{span}{See \code{\link[modreg]{loess}}.}
  \item{family}{See \code{\link[modreg]{loess}}.}
  \item{log.it}{logical value.}
}
\details{
Please refer to references.
}
\value{
The normalized intensities.
}
\references{
Astrand, M. (2003) \url{http://www.math.chalmers.se/~magnusaa/maffy/}}
\author{Magnus Astrand}
\seealso{ \code{\link{maffy.subset}}}
\examples{
     data(affybatch.example)
     x <- pm(affybatch.example)[1:2000,1:3]
     mva.pairs(x)
     x <- maffy.normalize(x,subset=1:nrow(x))
     mva.pairs(x)
}
\keyword{internal}





