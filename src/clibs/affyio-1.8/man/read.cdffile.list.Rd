\name{read.cdffile.list}
\alias{read.cdffile.list}
\title{Read CDF file into an R list}
\description{This function reads the entire contents of a cdf file into
  an R list structure
}
\usage{read.cdffile.list(filename, cdf.path = getwd())
}
\arguments{
\item{filename}{name of CDF file}
\item{cdf.path}{path to cdf file}
}
\value{returns a \code{list} structure. The exact contents may vary
depending on the file format of the cdf file (see \code{\link{check.cdf.type}})
}
\details{
Note that this function can be very memory intensive with large CDF files.
}
\author{B. M. Bolstad <bmb@bmbolstad.com>}
\keyword{IO}
