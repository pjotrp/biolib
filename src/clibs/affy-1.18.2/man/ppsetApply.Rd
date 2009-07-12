\name{ppsetApply}
\alias{ppsetApply}
\alias{ppset.ttest}
\title{ Apply a function over the ProbeSets in an AffyBatch }
\description{
  Apply a function over the ProbeSets in an AffyBatch
}
\usage{
ppsetApply(abatch, FUN, genenames = NULL, ...)

ppset.ttest(ppset, covariate, pmcorrect.fun = pmcorrect.pmonly, ...)
}
\arguments{
  \item{abatch}{ An object inheriting from \code{AffyBatch}.}
  \item{ppset}{ An object of class \code{ProbeSet}.}
  \item{covariate}{ the name a covariate in the slot \code{phenoData}.}
  \item{pmcorrect.fun}{ a function to corrrect PM intensities}
  \item{FUN}{ A function working on a \code{ProbeSet} }
  \item{genenames}{ A list of Affymetrix probesets ids to work with. All
  probe set ids used when \code{NULL}.}
  \item{\dots}{ Optional parameters to the function \code{FUN} }
}
\value{
  Returns a \code{list} of objects, or values, as returned by the
  function \code{FUN}
  for each \code{ProbeSet} it processes.
}
\author{Laurent Gautier <laurent@cbs.dtu.dk>}
\seealso{\code{\link[affy]{ProbeSet-class}} }
\examples{
ppset.ttest <- function(ppset, covariate, pmcorrect.fun = pmcorrect.pmonly, ...) {
  probes <- do.call("pmcorrect.fun", list(ppset))
  my.ttest <- function(x) {
    y <- split(x, get(covariate))
    t.test(y[[1]], y[[2]])$p.value
  }
  r <- apply(probes, 1, my.ttest)
  return(r)
}

## create a dataset
data(affybatch.example)
abatch <- merge(affybatch.example, affybatch.example2)
intensity(abatch) <- 2^jitter(log2(intensity(abatch)),1,1)
chip.variate <- c("a", "b", "a", "a", "b", "a")
phenoData(abatch) <- new("AnnotatedDataFrame", data=data.frame(whatever=chip.variate))
## run a test over _all_ probes.
all.ttest <- ppsetApply(abatch, ppset.ttest, covariate="whatever")

}
\keyword{ manip }
