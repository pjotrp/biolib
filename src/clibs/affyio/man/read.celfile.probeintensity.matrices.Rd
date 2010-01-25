\name{read.celfile.probeintensity.matrices}
\alias{read.celfile.probeintensity.matrices}
\title{Read PM or MM from CEL file into matrices}
\description{This function reads PM, MM or both types of intensities
  into matrices. These matrices have all the probes for a probeset in
  adjacent rows
}
\usage{read.celfile.probeintensity.matrices(filenames, cdfInfo, rm.mask=FALSE, rm.outliers=FALSE, rm.extra=FALSE, verbose=FALSE, which= c("pm","mm","both"))
}
\arguments{
  \item{filenames}{a character vector of filenames}
  \item{cdfInfo}{a list with items giving PM and MM locations for
    desired probesets. In same structure as returned by \code{\link[makecdfenv]{make.cdf.package}}}
  \item{rm.mask}{a \code{\link{logical}}. Return these probes as NA if
      there are in the [MASK] section of the CEL file}
  \item{rm.outliers}{a \code{\link{logical}}. Return these probes as NA if
      there are in the [OUTLIERS] section of the CEL file}.
  \item{rm.extra}{a \code{\link{logical}}. Return these probes as NA if
      there are in the [OUTLIERS] section of the CEL file}.
  \item{verbose}{a \code{\link{logical}}. When true the parsing routine
    prints more information, typically useful for debugging.}

  \item{which}{a string specifing which probe type to return}
  
}
\value{returns a \code{\link{list}} of \code{\link{matrix}} items. One
  matrix contains PM probe intensities, with probes in rows and arrays
  in columns
}
\author{B. M. Bolstad <bmb@bmbolstad.com>}
\keyword{IO}
