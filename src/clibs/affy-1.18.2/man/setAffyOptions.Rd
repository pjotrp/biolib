\name{.setAffyOptions}
\alias{.setAffyOptions}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{ ~~function to set options ~~ }
\description{
  ~~ Set the options for the package 
}
\usage{
.setAffyOptions(affy.opt = NA)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{affy.opt}{ A list structure of options. If \code{NA}, the
    default options are set.}
}
\details{
  See the vignettes to know more. This function could disappear in favor
  of a more general one the package Biobase
}
\value{
  The function is used for its side effect. Nothing is returned.
}
\author{ Laurent }
\examples{
affy.opt <- getOption("BioC")$affy

.setAffyOptions(affy.opt)

}
\keyword{ manip }
