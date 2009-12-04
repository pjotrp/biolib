\name{justRMA}
\alias{justRMA}
\alias{just.rma}
\title{Read CEL files into an ExpressionSet}
\description{
  Read CEL files and compute an expression measure without using an AffyBatch.}
\usage{
just.rma(\dots, filenames = character(0),
               phenoData = new("AnnotatedDataFrame"),
               description = NULL,
               notes = "",
               compress = getOption("BioC")$affy$compress.cel,
               rm.mask = FALSE, rm.outliers = FALSE, rm.extra = FALSE,
               verbose=FALSE, background=TRUE, normalize=TRUE,
               bgversion=2, destructive=FALSE, cdfname = NULL)

justRMA(\dots, filenames=character(0),
              widget=getOption("BioC")$affy$use.widgets,
              compress=getOption("BioC")$affy$compress.cel,
              celfile.path=getwd(),
              sampleNames=NULL,
              phenoData=NULL,
              description=NULL,
              notes="",
              rm.mask=FALSE, rm.outliers=FALSE, rm.extra=FALSE,
              hdf5=FALSE, hdf5FilePath=NULL,verbose=FALSE,
              normalize=TRUE, background=TRUE, 
              bgversion=2, destructive=FALSE, cdfname = NULL)
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
  \item{hdf5}{use of hdf5 ? (not available yet)}
  \item{hdf5FilePath}{a filename to use with hdf5 (not available yet).}
  \item{verbose}{verbosity flag.}
  \item{widget}{a logical specifying if widgets should be used.}
  \item{celfile.path}{a character denoting the path \code{ReadAffy}
    should look for cel files.}
  \item{sampleNames}{a character vector of sample names to be used in
    the \code{AffyBatch}.}
    \item{normalize}{logical value. If \code{TRUE}, then normalize data using
    quantile normalization.}
  \item{background}{logical value. If \code{TRUE}, then background correct
    using RMA background correction.}
  \item{bgversion}{integer value indicating which RMA background to use
    1: use background similar to pure R rma background given in affy version 1.0 - 1.0.2
    2: use background similar to pure R rma background given in affy version 1.1 and above}
   \item{destructive}{logical value. If \code{TRUE}, then works on the PM matrix in place
    as much as possible, good for large datasets.}
   \item{cdfname}{Used to specify the name of an alternative cdf package. If set to
     \code{NULL}, then the usual cdf package based on Affymetrix' mappings
     will be used.}
}
\details{
\code{justRMA} is a wrapper for \code{just.rma} that permits the
user to read in phenoData, MIAME information, and CEL files using
widgets. One can also define files where to read phenoData and MIAME
information.

If the function is called with no arguments \code{justRMA()}, then all the CEL
files in the working directory are read, converted to an expression
measure using RMA and put into an \code{\link[Biobase:class.ExpressionSet]{ExpressionSet}}.
However, the arguments give the user great flexibility.
  
\code{phenoData} is read using \code{\link[Biobase]{read.AnnotatedDataFrame}}. If a
character is given, it tries to read the file with that name to obtain the
\code{AnnotatedDataFrame} object as described in \code{\link[Biobase]{read.AnnotatedDataFrame}}.
If left \code{NULL} and \code{widget=FALSE} (\code{widget=TRUE} is not currently
supported), then a default object is created.
It will be an object of class \code{\link[Biobase.class.AnnotatedDataFrame]{AnnotatedDataFrame}}
with its pData being a data.frame with column x indexing the CEL files.

\code{description} is read using \code{\link[Biobase]{read.MIAME}}. If a
character is given, it tries to read the file with that name to obtain a
\code{MIAME} instance. If left \code{NULL} but \code{widget=TRUE}, then
widgets are used. If left \code{NULL} and \code{widget=FALSE}, then an
empty instance of \code{MIAME} is created..

The arguments \code{rm.masks}, \code{rm.outliers}, \code{rm.extra} are
passed along to the function \code{read.celfile}.
}
\value{
  An \code{ExpressionSet} object, containing expression values identical to
  what one would get from running \code{rma} on an \code{AffyBatch}.
}
\author{In the beginning: James MacDonald <jmacdon@med.umich.edu>
Supporting routines, maintenance and just.rma: Ben Bolstad <bmb@bmbolstad.com>}
\seealso{\code{\link[affy]{rma}},\code{\link[affy]{ReadAffy}}}
\keyword{manip}
