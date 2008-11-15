\name{affy-options}
\alias{affy-options}
\title{Options for the affy package}
\description{
  Description of the options for the affy package.
}
\note{
  The affy package options are contained in the Bioconductor options.
  The options are:
  \begin{itemize}
  \item \code{use.widgets}: a logical used to decide on the default of
  widget use.
  \item \code{compress.cel}: a logical
  \item \code{compress.cdf}: a logical
  \item \code{probes.loc}: a list. Each element of the list is it self a
  list with two elements {\it what} and {\it where}. When looking for
  the informations about the locations of the probes on the array, the
  elements in the list will be looked at one after the other. The first
  one for which {\it what} and {\it where} lead to the matching
  locations information is used. The element {\it what} can be one of
  {\it package}, {\it environment} or {\it file}. The element {\it where}
  depends on the corresponding element {\it what}.
  \begin{itemize}
  \item if {\it package}: location for the package (like it would be for
  the argument \code{lib.loc} for the function \code{library}.
  \item if {\it environment}: an \code{environment} to look for the
  information
  (like the argument \code{env} for the function \code{get}).
  \item if {\it file}: a \code{character} with the path in which a CDF
  file can be found.
  \end{itemize}
  \end{itemize}
}
\examples{
## get the options
opt <- getOption("BioC")
affy.opt <- opt$affy

## list their names
names(affy.opt)

## set the option compress.cel
affy.opt$compress.cel <- TRUE
options(BioC=opt)
}
\keyword{manip}
