\name{bg.correct}
\alias{bg.correct}
\alias{bg.correct.none} %took out .pmonly casue rma is pm-only
%\alias{bg.correct.subtractmm}
\alias{bg.correct.rma}
\alias{bg.correct.mas}
\title{Background Correction}
\description{
Background corrects probe intensities in an object of class
\code{\link[affy:AffyBatch-class]{AffyBatch}}.
}
\usage{
bg.correct(object, method, ...)

bg.correct.rma(object,...)
bg.correct.mas(object, griddim)
bg.correct.none(object, ...)
}

\arguments{
  \item{object}{An object of class \code{\link[affy:AffyBatch-class]{AffyBatch}}.}
  \item{method}{A \code{character} that defines what background
    correction method will be used. Available methods are given by
    \code{bg.correct.methods}. }  
  \item{griddim}{grid dimension used for mas background estimate. The array
    is divided into griddm equal parts. Default is 16.}
  \item{...}{arguments to pass along to the engine function.}
}
\details{
  The name of the method to apply must be double-quoted.
  Methods provided with the package are currently:
  \begin{itemize}
  \item bg.correct.none: returns \code{object} unchanged.
  \item bg.correct.chipwide: noise correction as described in a
  `white paper' from Affymetrix.
  \item bg.correct.rma: the model based correction used by the RMA
  expression measure.
  \end{itemize}

  They are listed in the variable \code{bg.correct.methods}. The user must
  supply the word after "bg.correct", i.e none, subtractmm, rma, etc...

  More details are available in the vignette.

  R implementations similar in function to the internal implemntation used by \code{bg.correct.rma} are in
  \code{\link{bg.adjust}}.
  
}  
\value{
  An \code{\link[affy:AffyBatch-class]{AffyBatch}} for which the
  intensities have been background adjusted.
  For some methods (RMA), only PMs are corrected and the MMs remain the
  same. 
}

\examples{
    data(affybatch.example)

    ##bgc will be the bg corrected version of affybatch.example 
    bgc <- bg.correct(affybatch.example,method="rma") 

    ##This plot shows the tranformation
    plot(pm(affybatch.example)[,1],pm(bgc)[,1],log="xy",
	main="PMs before and after background correction")

}
\keyword{manip}








