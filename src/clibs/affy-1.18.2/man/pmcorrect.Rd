\name{pmcorrect}
\alias{pmcorrect}
\alias{pmcorrect.methods}
\alias{pmcorrect.pmonly} %took out .pmonly casue rma is pm-only
\alias{pmcorrect.mas}
\alias{pmcorrect.subtractmm}
%- Also NEED an `\alias' for EACH other topic documented here.
\title{PM Correction}
\description{
  Corrects the PM intensities in a \code{\link[affy:ProbeSet-class]{ProbeSet}}
    for nonspecific binding.
  }
\usage{
pmcorrect.pmonly(object)

pmcorrect.subtractmm(object)

pmcorrect.mas(object, contrast.tau=0.03, scale.tau=10, delta=2^(-20))
}
\arguments{
  \item{object}{An object of class \code{\link[affy:ProbeSet-class]{ProbeSet}}.}
  \item{contrast.tau}{a number denoting the contrast tau parameter in
    the MAS 5.0 
    pm correction algorithm.}
  \item{scale.tau}{a number denoting the scale tau parameter in
    the MAS 5.0 
    pm correction algorithm.}
  \item{delta}{a number denoting the detla parameter in
    the MAS 5.0 
    pm correction algorithm.}
}
\details{
These are the pm correction methods perfromed by Affymetrix MAS 4.0
(subtractmm) and MAS 5.0 (mas). See the Affymetrix Manual for details.
pmonly does what you think: does not change the PM values.}
\value{A \code{\link[affy:ProbeSet-class]{ProbeSet}} for which the
  \code{pm} slot contains the  corrected  PM values.}

\references{Affymetrix MAS 4.0 and 5.0 manual}

\examples{
data(affybatch.example)
gn <- geneNames(affybatch.example)
pps <- probeset(affybatch.example, gn[1])[[1]]

pps.pmonly <- pmcorrect.pmonly(pps)
pps.subtractmm <- pmcorrect.subtractmm(pps)
pps.mas5 <- pmcorrect.mas(pps)
par(mfrow=c(2,2))
#plot(pm(pps.pmonly), pm(pps.subtractmm))
#plot(pm(pps.pmonly),pm(pps.mas5))
#plot(pm(pps.subtractmm),pm(pps.mas5))
}
\keyword{manip}



