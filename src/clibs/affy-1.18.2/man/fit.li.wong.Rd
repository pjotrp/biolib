\name{fit.li.wong}
\alias{fit.li.wong}
\alias{li.wong}

\title{Fit Li and Wong Model to a Probe Set}
\description{Fits the model described in Li and Wong (2001) to a probe
  set with I chips and J probes.
}
\usage{
fit.li.wong(data.matrix, remove.outliers=TRUE, normal.array.quantile=0.5,
            normal.resid.quantile=0.9, large.threshold=3, large.variation=0.8,
            outlier.fraction=0.14, delta=1e-06, maxit=50,
            outer.maxit=50,verbose=FALSE, ...)

li.wong(data.matrix,remove.outliers=TRUE, normal.array.quantile=0.5,
            normal.resid.quantile=0.9, large.threshold=3, large.variation=0.8,
            outlier.fraction=0.14, delta=1e-06, maxit=50,
            outer.maxit=50,verbose=FALSE)

}
\arguments{
  \item{data.matrix}{an I x J matrix containing the probe set
    data. Typically the i,j entry will contain the PM-MM value for probe
    pair j in chip i. Another possible use, is to use PM instead of PM-MM.}
  \item{remove.outliers}{logical value indicating if the algorithm
    will remove outliers according to the procedure described in Li and
    Wong (2001).}
  \item{large.threshold}{used to define outliers.}
  \item{normal.array.quantile}{quantile to be used when determining what
    a normal SD is. probes or chips having estimates with SDs bigger
    than the quantile \code{normal.array.quantile} of all SDs x
    \code{large.threshold} }
  \item{normal.resid.quantile}{any residual  bigger than the
    \code{normal.resid.quantile} quantile of all residuals x
    \code{large.threshold} is considered an outlier}
  \item{large.variation}{any probe or chip describing more than this
    much total variation is considered an outlier}
  \item{outlier.fraction}{this is the maximum fraction of single
    outliers that can be in the same probe or chip.}
  \item{delta}{ numerical value used to define the stopping
    criterion. }
  \item{maxit}{ maximum number of iterations when fitting the model.}
  \item{outer.maxit}{ maximum number of iterations of defined outliers.}
  \item{verbose}{logical value. If \code{TRUE} information is given of
    the status of the algorithm.}
  \item{...}{       }
}
\details{
  This is Bioconductor's implementation of the Li and Wong algorithm. The
  Li and Wong PNAS 2001 paper was followed. However, you will not get
  the same results as you would get with dChip. dChip is not open source
  so it is not easy to reproduce. 

  Notice that this iterative algorithm will not always converge.
  If you run the
  algorithm on thousands of probes expect some non-convergence
  warnings. These are more likely when few arrays are used. We recommend
  using this method only if you have 10 or more arrays.

  Please refer to references for more details.
}

\value{\code{li.wong} returns a vector of expression measures (or column
  effects) followed by their respective standard error estimates. It
  was designed to work with \code{express} which is no longer part of
  the package.

  \code{fit.li.wong} returns much more. Namely, a list containing the
  fitted parameters and relevant information. 
  \item{theta}{fitted thetas.}
  \item{phi}{fitted phis.}
  \item{sigma.eps}{estimated standard deviation of the error term.}
  \item{sigma.theta}{estimated standard error of theta.}
  \item{sigma.phi}{estimated standard error of phis.}
  \item{theta.outliers}{logical vector describing which chips (thetas) are considered
    outliers (\code{TRUE}).}
  \item{phi.outliers}{logical vector describing which probe sets (phis) are
    considered outliers (\code{TRUE})}
  \item{convergence1}{logical value. If \code{FALSE} the algorithm did
    not converge when fitting the phis and thetas.}
  \item{convergence2}{logical value. If \code{FALSE} the algorithm did
    not converge in deciding what are outliers.}
  \item{iter}{number of iterations needed to achieve convergence.}
  \item{delta}{difference between thetas when iteration stopped.}
}
\examples{

    x <- sweep(matrix(2^rnorm(600),30,20),1,seq(1,2,len=30),FUN="+")
    fit1 <- fit.li.wong(x)
    plot(x[1,])
    lines(fit1$theta)
  }
\references{
  Li, C. and Wong, W.H. (2001) \emph{Genome Biology} \bold{2}, 1--11.\cr

  Li, C. and Wong, W.H. (2001) \emph{Proc. Natl. Acad. Sci USA}
  \bold{98}, 31--36.
}
\author{Rafael A. Irizarry, Cheng Li, Fred A. Wright, Ben Bolstad}
\seealso{ \code{\link{li.wong}}, \code{\link{expresso}}}
\keyword{manip}
\keyword{models}


