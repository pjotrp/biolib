\name{read.affybatch}
\alias{read.affybatch}
\alias{AllButCelsForReadAffy}
\alias{ReadAffy}
\title{Read CEL files into an AffyBatch}
\description{
  Read CEL files into an Affybatch.
}
\usage{
read.affybatch(\dots, filenames = character(0),
               phenoData = new("AnnotatedDataFrame"),
               description = NULL,
               notes = "",
               compress = getOption("BioC")$affy$compress.cel,
               rm.mask = FALSE, rm.outliers = FALSE, rm.extra = FALSE,
               verbose = FALSE,sd=FALSE, cdfname = NULL)

ReadAffy(\dots, filenames=character(0),
              widget=getOption("BioC")$affy$use.widgets,
              compress=getOption("BioC")$affy$compress.cel,
              celfile.path=NULL,
              sampleNames=NULL,
              phenoData=NULL,
              description=NULL,
              notes="",
              rm.mask=FALSE, rm.outliers=FALSE, rm.extra=FALSE,
              verbose=FALSE,sd=FALSE, cdfname = NULL)
}
\arguments{
  \item{\dots}{file names separated by comma.}
  \item{filenames}{file names in a character vector.}
  \item{phenoData}{a \code{\link[Biobase:class.AnnotatedDataFrame]{AnnotatedDataFrame}} object.}
  \item{description}{a \code{\link[Biobase:class.MIAME]{MIAME}} object.}
  \item{notes}{notes.}
  \item{compress}{are the CEL files compressed?}
  \item{rm.mask}{should the spots marked as 'MASKS' set to \code{NA}?}
  \item{rm.outliers}{should the spots marked as 'OUTLIERS' set to \code{NA}?}
  \item{rm.extra}{if \code{TRUE}, then overrides what is in \code{rm.mask} and \code{rm.oultiers}.}
  \item{verbose}{verbosity flag.}
  \item{widget}{a logical specifying if widgets should be used.}
  \item{celfile.path}{a character denoting the path \code{ReadAffy}
    should look for cel files.}
  \item{sampleNames}{a character vector of sample names to be used in
    the \code{AffyBatch}.}
  \item{sd}{should the standard deviation values in the CEL file be read
    in? Since these are typically not used default is not to read them
    in. This also save lots of memory.}
   \item{cdfname}{used to specify the name of an alternative cdf package. If set to
     \code{NULL}, then the usual cdf package based on Affymetrix' mappings
     will be used.}
}
\details{
\code{ReadAffy} is a wrapper for \code{read.affybatch} that permits the
user to read in phenoData, MIAME information, and CEL files using
widgets. One can also define files where to read phenoData and MIAME
information.

If the function is called with no arguments \code{ReadAffy()} all the CEL
files in the working directory are read and put into an \code{AffyBatch}.
However, the arguments give the user great flexibility.
  
\code{phenoData} is read using \code{\link[Biobase]{read.AnnotatedDataFrame}}. If a
character is given it tries to read the file with that name
to obtain the \code{AnnotationDataFrame} object as described in \code{\link[Biobase]{read.AnnotatedDataFrame}}.
If left \code{NULL} and \code{widget=FALSE} (\code{widget=TRUE} is not currently
supported), then a default object is created.
It will be an object of class \code{\link[Biobase:class.AnnotatedDataFrame]{AnnotatedDataFrame}}
with its pData being a data.frame with column x indexing the CEL files.

\code{AllButCelsForReadAffy} is an internal function that gets called
by \code{ReadAffy}. It gets all the information except the cel intensities.

\code{description} is read using \code{\link[Biobase]{read.MIAME}}. If a
character is given, then it tries to read the file with that name to obtain a
\code{MIAME} instance. If left \code{NULL} but \code{widget=TRUE}, then
widgets are used. If left \code{NULL} and \code{widget=FALSE}, then an
empty instance of \code{MIAME} is created.
}
\value{
  An \code{AffyBatch} object.
}
\author{Ben Bolstad \email{bmb@bmbolstad.com} (read.affybatch),
  Laurent Gautier,
  and Rafael A. Irizarry (ReadAffy)}
\seealso{\code{\link[affy:AffyBatch-class]{AffyBatch}}}
\examples{
if(require(affydata)){
     celpath <- system.file("celfiles", package="affydata")
     fns <- list.celfiles(path=celpath,full.names=TRUE)
 
     cat("Reading files:\n",paste(fns,collapse="\n"),"\n")
     ##read a binary celfile
     abatch <- ReadAffy(filenames=fns[1])
     ##read a text celfile
     abatch <- ReadAffy(filenames=fns[2])
     ##read all files in that dir
     abatch <- ReadAffy(celfile.path=celpath)
}
}
\keyword{manip}
