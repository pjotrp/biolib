\name{read.celfile}
\alias{read.celfile}
\title{Read a CEL file into an R list}
\description{This function reads the entire contents of a CEL file into
  an R list structure
}
\usage{read.celfile(filename,intensity.means.only=FALSE)
}
\arguments{
\item{filename}{name of CEL file}
\item{intensity.means.only}{If \code{TRUE} then read on only the MEAN section in INTENSITY}
}
\value{returns a \code{list} structure. The exact contents may vary
depending on the file format of the CEL file
}
\details{
The list has four main items. HEADER, INTENSITY, MASKS, OUTLIERS. Note
that INTENSITY is a list of three vectors MEAN, STDEV, NPIXELS. HEADER
is also a list. Both of MASKS and OUTLIERS are matrices.

}
\author{B. M. Bolstad <bmb@bmbolstad.com>}
\keyword{IO}
