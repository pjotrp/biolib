\name{expresso}
\alias{expresso}
\alias{bgcorrect.methods}
\alias{bgcorrect}

%- Also NEED an `\alias' for EACH other topic documented here.
\title{ From raw probe intensities to expression values }
\description{
  Goes from raw probe intensities to expression values
}
\usage{
expresso(
        afbatch,
    # background correction
        bg.correct = TRUE,
        bgcorrect.method = NULL,
        bgcorrect.param = list(),
    # normalize
        normalize = TRUE,
        normalize.method = NULL,
        normalize.param = list(),
    # pm correction
        pmcorrect.method = NULL,
        pmcorrect.param = list(),
    # expression values
        summary.method = NULL,
        summary.param = list(),
        summary.subset = NULL,
    # misc.
        verbose = TRUE,
%        warnings = TRUE,
        widget = FALSE)
}

\arguments{
  \item{afbatch}{ An \code{\link[affy:AffyBatch-class]{AffyBatch}} object }
  \item{bg.correct}{a boolean to express whether background correction
    is wanted or not.}
  \item{bgcorrect.method}{the name of the background adjustment method}
  \item{bgcorrect.param}{a list of parameters for bgcorrect.method (if needed/wanted)}
  \item{normalize}{ normalization step wished or not.}
  \item{normalize.method}{the normalization method to use}
  \item{normalize.param}{a list of parameters to be passed to the
    normalization method (if wanted).}
  \item{pmcorrect.method}{the name of the PM adjustement method}
  \item{pmcorrect.param}{a list of parameters for pmcorrect.method (if needed/wanted)}
  \item{summary.method}{the method used for the computation of expression values}
  \item{summary.param}{ a list of parameters to be passed to the
    \code{summary.method} (if wanted).}
  \item{summary.subset}{a list of 'affyids'. If \code{NULL}, a
    expression summary value is computed for everything on the chip.}
  \item{verbose}{logical value. If \code{TRUE} it writes out some
    messages.}
%  \item{warnings}{warning when something goes wrong}
  \item{widget}{a boolean to specify the use of widgets (the package
    tkWidget is required).}
}
\details{
    Some arguments can be left to \code{NULL} if the \code{widget=TRUE}.
  In this case, a widget pops up and let the user choose with the mouse.
  The arguments are: \code{AffyBatch},
  \code{bgcorrect.method}, \code{normalize.method}, \code{pmcorrect.method} and \code{summary.method}.

  For the mas 5.0 and 4.0 methods ones need to normalize after obtaining
  expression. The function \code{\link{affy.scalevalue.exprSet}} does this.

  To see what background methods are available you can look at the
  object \code{bgcorrect.methods}.
  
  For the Li and Wong summary method notice you will not get
  the same results as you would get with dChip. dChip is not open source
  so it is not easy to reproduce. 
  Notice also that this iterative algorithm will not always converge.
  If you run the algorithm on thousands of probes expect some non-convergence
  warnings. These are more likely when few arrays are used. We recommend
  using this method only if you have 10 or more arrays.
  Please refer to the \code{\link{fit.li.wong}} help page for more details.

}
\value{
  An object of class \code{\link[Biobase:class.ExpressionSet]{ExpressionSet}}, with an attribute
  \code{pps.warnings} as returned by the method \code{\link{computeExprSet}}.
}
\seealso{\code{\link[affy:AffyBatch-class]{AffyBatch}}}
\examples{
data(affybatch.example)

eset <- expresso(affybatch.example, bgcorrect.method="rma",
                 normalize.method="constant",pmcorrect.method="pmonly",
                 summary.method="avgdiff")

##to see options available for bg correction type:
bgcorrect.methods
}
\keyword{ manip }

