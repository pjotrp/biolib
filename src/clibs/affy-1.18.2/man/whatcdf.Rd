\name{whatcdf}
\alias{whatcdf}

\title{Find which CDF corresponds}
\description{
  Find which kind of CDF corresponds to a CEL file.
}
\usage{
whatcdf(filename, compress = getOption("BioC")$affy$compress.cel)
}
\arguments{
  \item{filename}{a '.CEL' file name}
  \item{compress}{boolean (file compressed or not}
}
\details{
  Information concerning the corresponding CDF file seems to be found in
  CEL files. This allows us to try to link CDF information automatically.
}
\value{
  a \code{character} with the name of the CDF
}
\seealso{\code{getInfoInAffyFile}, \code{read.celfile}}

\keyword{manip}

