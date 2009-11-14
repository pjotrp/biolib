\name{read.celfile.header}
\alias{read.celfile.header}
\title{Read header information from cel file}
\description{
  This function reads some of the header information (appears before probe
  intensity data) from the supplied cel file.
}
\usage{read.celfile.header(filename,info=c("basic","full"),verbose=FALSE)
}
\arguments{
  \item{filename}{name of CEL file. May be fully pathed}
  \item{info}{A string. \code{basic} returns the dimensions of the chip
    and the name of the CDF file used when the CEL file was
    produced. \code{full} returns more information in greater detail.}
  \item{verbose}{a \code{\link{logical}}. When true the parsing routine
    prints more information, typically useful for debugging.}
}
\value{
  A \code{list} data structure.
}
\author{B. M. Bolstad <bmb@bmbolstad.com>}
\keyword{IO}
