\name{generateExprVal.method.avgdiff}
\alias{generateExprVal.method.avgdiff}
\alias{generateExprVal.method.medianpolish}
\alias{generateExprVal.method.liwong}
\alias{generateExprVal.method.mas}



\title{Generate an expression value from the probes informations}
\description{
  Generate an expression from the probes
}
\usage{
generateExprVal.method.avgdiff(probes, ...)
generateExprVal.method.medianpolish(probes, ...)
generateExprVal.method.liwong(probes, ...)
generateExprVal.method.mas(probes, ...)

}
\arguments{
  \item{probes}{a matrix of probe intesities with rows representing
    probes and columns representing
    samples. Usually \code{pm(probeset)} where \code{probeset} is a
    of class \code{\link[affy:ProbeSet-class]{ProbeSet}}}
  \item{...}{extra arguments to pass to the respective function}
}
\value{
  A list containing entries:
  \item{exprs}{The expression values.}
  \item{se.exprs}{The standard error estimate.}
}
\examples{
  data(SpikeIn) ##SpikeIn is a ProbeSets
  probes <- pm(SpikeIn) 
  avgdiff <- generateExprVal.method.avgdiff(probes)
  medianpolish <- generateExprVal.method.medianpolish(probes)
  liwong <- generateExprVal.method.liwong(probes)
  playerout <- generateExprVal.method.playerout(probes)
  mas <- generateExprVal.method.mas(probes)
  
  concentrations <- as.numeric(sampleNames(SpikeIn))
  plot(concentrations,avgdiff$exprs,log="xy",ylim=c(50,10000),pch="a",type="b")
  points(concentrations,2^medianpolish$exprs,pch="m",col=2,type="b",lty=2)
  points(concentrations,liwong$exprs,pch="l",col=3,type="b",lty=3)
  points(concentrations,playerout$exprs,pch="p",col=4,type="b",lty=4)
  points(concentrations,mas$exprs,pch="p",col=4,type="b",lty=4)

  
}
\seealso{
  \code{\link{generateExprSet-methods},\code{\link{generateExprVal.method.playerout}}, \code{\link{li.wong}}, \code{\link{medianpolish}}}
}
\keyword{manip}
