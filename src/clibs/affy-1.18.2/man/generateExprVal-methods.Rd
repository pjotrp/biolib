\name{generateExprVal}
\alias{generateExprVal}
\alias{generateExprVal-methods}
\alias{generateExprVal.methods}
\alias{express.summary.stat}
\alias{express.summary.stat-methods}
\alias{express.summary.stat.methods}

\title{Compute a summary expression value from the probes intensities}
\description{
  Compute a summary expression value from the probes intensities
}
\usage{
generateExprVal.methods # vector of names of methods

express.summary.stat(x, pmcorrect, summary, ...)
express.summary.stat.methods # vector of names of methods
}
\arguments{
  \item{x}{a (\code{ProbeSet}}
  \item{pmcorrect}{the method used to correct the PM values before
    summarizing to an expression value.}
  \item{summary}{the method used to generate the expression value.}
  \item{...}{other parameters the method might need... (see the
    corresponding methods below...)}
}
\value{
  Returns a vector of expression values.
}
\examples{
data(affybatch.example)

p <- probeset(affybatch.example, "A28102_at")[[1]]

par(mfcol=c(5,2))
mymethods <- express.summary.stat.methods
nmet <- length(mymethods)
nc <- ncol(pm(p))

layout(matrix(c(1:nc, rep(nc+1, nc)), nc, 2), width = c(1, 1))

barplot(p)

results <- matrix(0, nc, nmet)
rownames(results) <- paste("sample", 1:nc)
colnames(results) <- mymethods

for (i in 1:nmet) {
  ev <- express.summary.stat(p, summary=mymethods[i], pmcorrect="pmonly")
  if (mymethods[[i]] != "medianpolish")
    results[, i] <- 2^(ev$exprs)
  else
    results[, i] <- ev$exprs
}

dotchart(results, labels=paste("sample", 1:nc))

}
\keyword{manip}
