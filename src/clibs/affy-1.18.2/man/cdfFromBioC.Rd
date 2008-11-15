\name{cdfFromBioC}
\alias{cdfFromBioC}
\alias{cdfFromData}
\alias{cdfFromLibPath}
\alias{cdfFromEnvironment}

%- Also NEED an '\alias' for EACH other topic documented here.
\title{Functions to obtain CDF files}
\description{
  A set of functions to obtain CDF files from various locations.
}
\usage{
cdfFromBioC(cdfname, lib = .libPaths()[1], verbose = TRUE)
cdfFromData(cdfname, pkg, verbose=TRUE)
cdfFromLibPath(cdfname, lib = NULL, verbose=TRUE)
cdfFromEnvironment(cdfname, where, verbose=TRUE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{cdfname}{ The CDF desired }
  \item{lib}{ Directory to install the CDF package to }
  \item{pkg}{What package to search}
  \item{where}{What environment to search}
  \item{verbose}{Controls extra output}  
}
\details{
  These functions all take a requested CDF environment name and will
  attempt to locate that environment in the appropriate location (a
  package's data directory, as a CDF package in the .libPaths(), from a
  loaded environment or on the Bioconductor website.  If the environment
  can not be found, it will return a list of the methods tried that failed.
}
\value{
  The CDF environment or a list detailing the failed locations.
}
\author{Jeff Gentry}
\keyword{utilities}
