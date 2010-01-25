\name{check.cdf.type}
\alias{check.cdf.type}
\title{CDF file format function}
\description{This function returns a text string giving the file format
  for the supplied filename
}
\usage{check.cdf.type(filename)
}
\arguments{
  \item{filename}{fullpath to a cdf file}
}
\value{Returns a string which is currently one of:

    \item{text}{the cdf file is of the text format}
    \item{xda}{the cdf file is of the binary format used in GCOS}
    \item{unknown}{the parser can not handle this format or does not
      recognize this file as a CDF file}

  }

\author{B. M. Bolstad <bmb@bmbolstad.com>}
\keyword{IO}
