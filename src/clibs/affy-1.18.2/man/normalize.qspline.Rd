\name{normalize.qspline}
\alias{qspline-normalize}
\alias{normalize.qspline}
\alias{normalize.AffyBatch.qspline}
\title{Normalize arrays}
\description{
  normalizes arrays in an AffyBatch each other or to a set of target intensities
}
\usage{
normalize.AffyBatch.qspline(abatch,type=c("together", "pmonly", "mmonly",
                 "separate"), ...)

normalize.qspline(x, target = NULL, samples = NULL, 
                  fit.iters = 5, min.offset = 5, 
                  spline.method = "natural", smooth = TRUE,
                  spar = 0, p.min = 0, p.max = 1.0, 
                  incl.ends = TRUE, converge = FALSE, 
                  verbose = TRUE, na.rm = FALSE)
}
\arguments{
  \item{x}{a \code{data.matrix} of intensities}
  \item{abatch}{an \code{AffyBatch}}
  \item{target}{numerical vector of intensity values to normalize to.
                (could be the name for one of the celfiles in 'abatch')}
  \item{samples}{numerical, the number of quantiles to be used for spline.
                 if (0,1], then it is a sampling rate}
  \item{fit.iters}{number of spline interpolations to average}
  \item{min.offset}{minimum span between quantiles (rank difference) for the
                    different fit iterations}
  \item{spline.method}{specifies the type of spline to be used. Possible values are 
                       `"fmm"', `"natural"', and `"periodic"'.}
  \item{smooth}{logical, if `TRUE', smoothing splines are used on the quantiles}
  \item{spar}{smoothing parameter for `splinefun', typically in (0,1].}
  \item{p.min}{minimum percentile for the first quantile}
  \item{p.max}{maximum percentile for the last quantile}
  \item{incl.ends}{include the minimum and maximum values from the normalized
                   and target arrays in the fit}
  \item{converge}{(currently unimplemented)}
  \item{verbose}{logical, if `TRUE' then normalization progress is reported}
  \item{na.rm}{logical, if `TRUE' then handle NA values (by ignoring
    them)}
  \item{type}{A string specifying how the normalization should be
    applied. See details for more.}
  \item{...}{Optional parameters to be passed through}
}
\value{
  a normalized \code{AffyBatch}.
}
\details{
  This normalization method uses the quantiles from each array and the 
  target to fit a system of cubic splines to normalize the data. The 
  target should be the mean (geometric) or median of each probe but could 
  also be the name of a particular chip in the \code{abatch} object.

  Parameters setting can be of much importance when using this method.
  The parameter \code{fit.iter} is used as a starting point to find a
  more appropriate value. Unfortunately the algorithm used do not
  converge in some cases. If this happens, the \code{fit.iter} value is
  used and a warning is thrown. Use of different settings for the
  parameter \code{samples} was reported to give good results. More
  specifically, for about 200   data points use
  \code{samples = 0.33}, for about 2000  data points use
  \code{samples = 0.05}, for about 10000 data points use
  \code{samples = 0.02}
  (thanks to Paul Boutros).
  
  The \code{type} argument should be one of
  \code{"separate","pmonly","mmonly","together"} which indicates whether
  to normalize only one probe type (PM,MM) or both together or separately.
  

  
}
\author{
  Laurent and Workman C.
}
\references{
  Christopher Workman, Lars Juhl Jensen, Hanne Jarmer, Randy Berka,
     Laurent Gautier, Henrik Bj{\o}rn Nielsen, Hans-Henrik Saxild, Claus
     Nielsen, S{\o}ren Brunak, and Steen Knudsen. A new non-linear normal-
     ization method for reducing variability in dna microarray experiments.
     Genome Biology, accepted, 2002
}
\keyword{manip}
