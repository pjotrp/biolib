\name{AffyRNAdeg}
\alias{AffyRNAdeg}
\alias{summaryAffyRNAdeg}
\alias{plotAffyRNAdeg}
\title{Function to assess RNA degradation in Affymetrix GeneChip data. }
\description{
  Uses ordered probes in probeset to detect possible RNA degradation.
  Plots and statistics used for evaluation.
}
\usage{
AffyRNAdeg(abatch,log.it=TRUE)
summaryAffyRNAdeg(rna.deg.obj,signif.digits=3)
plotAffyRNAdeg(rna.deg.obj, transform = "shift.scale", cols = NULL,
                 ...)
}
%- maybe also `usage' for other objects documented here.
\arguments{
  \item{abatch}{An object of class \code{\link{AffyBatch-class}}.}
  \item{log.it}{A logical argument: If log.it=T, then probe data is log2 tranformed}
  \item{rna.deg.obj}{Output from AffyRNAdeg}
  \item{signif.digits}{Number of significant digits to show.}
  \item{transform}{Possible choices are "shift.scale","shift.only", and "neither".  "Shift" vertically staggers the plots for individual chips, to make the display easier to read. "Scale" normalizes so that standard deviation is equal to 1.    }
  \item{cols}{A vector of colors for plot, length = number of chips}
  \item{...}{further arguments for \code{\link{plot}} function.}
}
\details{Within each probeset, probes are numbered directionally from
  the 5' end to the 3' end. Probe intensities are averaged by probe
  number, across all genes.   If log.it=\code{FALSE} and
  transform="Neither", then 
  plotAffyRNAdeg  simply shows these means for each chip.  Shifted and
  scaled versions of the plot can make it easier to see.   
 
}
\value{
  \code{AffyRNAdeg} returns a list with the following components:
  \item{sample.names }{names of samples, derived from affy batch object}
  \item{means.by.number}{average intensity by probe position}
  \item{ses}{standard errors for probe position averages}
  \item{slope}{from linear regression of means.by.number}
  \item{pvalue}{from linear regression of means.by.number}
}
\examples{
data(affybatch.example)
RNAdeg<-AffyRNAdeg(affybatch.example)
plotAffyRNAdeg(RNAdeg)

}
\author{ Leslie Cope }
\keyword{hplot}% at least one, from doc/KEYWORDS
\keyword{manip}% at least one, from doc/KEYWORDS
