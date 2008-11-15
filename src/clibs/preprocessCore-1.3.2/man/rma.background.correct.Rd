\name{rma.background.correct}
\alias{rma.background.correct}
\title{RMA Background Correction}
\description{Background correct each column of a matrix
}
\usage{
  rma.background.correct(x,copy=TRUE)
}
\arguments{
  \item{x}{A matrix of intensities where each column corresponds to a
    chip and each row is a probe.}
  \item{copy}{Make a copy of matrix before background correctiong. Usually safer to
    work with a copy, but in certain situations not making a copy of the
    matrix, but instead background correcting it in place will be more memory friendly.}
}
\details{
	Assumes PMs are a convolution of normal and exponentional. So we
  observe X+Y where X is backround and Y is signal. \code{bg.adjust}
    returns E[Y|X+Y, Y>0] as our backround corrected
    PM. 

}

\value{
  A RMA background corrected \code{matrix}.
}
\references{
Bolstad, BM (2004) \emph{Low Level Analysis of High-density
    Oligonucleotide Array Data: Background, Normalization and
    Summarization}. PhD Dissertation. University of California,
  Berkeley. pp 17-21	

  }

\author{Ben Bolstad, \email{bmbolstad.com}}

\keyword{manip}
