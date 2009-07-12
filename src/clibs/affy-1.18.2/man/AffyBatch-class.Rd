\name{AffyBatch-class}
\docType{class}
\alias{AffyBatch-class}
\alias{AffyBatch,ANY}
\alias{AffyBatch}
\alias{probes}
\alias{geneNames}
\alias{geneNames<-}
\alias{getCdfInfo}
\alias{image}
\alias{indexProbes}
\alias{intensity<-}
\alias{intensity}
\alias{pmindex}
\alias{mmindex}
\alias{probeset}
\alias{$.AffyBatch}
\alias{cdfName}
\alias{cdfName,AffyBatch-method}
\alias{checkValidFilenames}
\alias{probes,AffyBatch-method}
\alias{exprs,AffyBatch-method}
\alias{exprs<-,AffyBatch,ANY-method}
\alias{se.exprs,AffyBatch-method}
\alias{se.exprs<-,AffyBatch-method}
\alias{featureNames,AffyBatch-method}
\alias{featureNames<-,AffyBatch-method}
\alias{geneNames,AffyBatch-method}
\alias{geneNames<-,AffyBatch,ANY-method}
\alias{getCdfInfo,AffyBatch-method}
\alias{image,AffyBatch-method}
\alias{initialize,AffyBatch-method}
\alias{indexProbes,AffyBatch-method}
\alias{intensity<-,AffyBatch-method}
\alias{intensity,AffyBatch-method}
\alias{pmindex,AffyBatch-method}
\alias{mmindex,AffyBatch-method}
\alias{probeset,AffyBatch-method}
\alias{boxplot,AffyBatch-method}
\alias{dim,AffyBatch-method}
\alias{row,AffyBatch-method}
\alias{col,AffyBatch-method}
\alias{show,AffyBatch-method}
\alias{pm,AffyBatch-method}
\alias{pm<-,AffyBatch,ANY-method}
\alias{mm,AffyBatch-method}
\alias{mm<-,AffyBatch,ANY-method}
\alias{probeNames,AffyBatch-method}
\alias{hist,AffyBatch-method}
\alias{[<-,AffyBatch-method}
\alias{[,AffyBatch-method}
\alias{[[,AffyBatch-method}
\alias{length,AffyBatch-method}
\alias{bg.correct,AffyBatch,character-method}
\alias{indexProbes,AffyBatch,character-method}
\alias{indexProbes,AffyBatch,missing-method}
\alias{computeExprSet,AffyBatch,character,character-method}
\alias{cdfName,AffyBatch-method}
\alias{updateObject,AffyBatch-method}
\title{Class AffyBatch}
\description{This is a class representation for Affymetrix GeneChip probe
  level data. The main component are the intensities from multiple
  arrays of the same \code{CDF} type. It extends \code{\link[Biobase:class.eSet]{eSet}}.}
\section{Objects from the Class}{
  Objects can be created using the function \code{\link{read.affybatch}}
  or the wrapper \code{\link{ReadAffy}}.
}
\section{Slots}{
  \describe{
    \item{\code{cdfName}:}{Object of class \code{character} representing the name of
      \code{CDF} file associated with the arrays in the
      \code{AffyBatch}.}
    \item{\code{nrow}:}{Object of class \code{integer} representing
      the physical number of rows in the arrays.}
    \item{\code{ncol}:}{Object of class \code{integer} representing
      the physical number of columns in the arrays.}
    \item{\code{assayData}:}{Object of class \code{AssayData}
      containing the raw data, which will be at minimum a matrix of
      intensity values. This slot can also hold a matrix of standard
      errors if the 'sd' argument is set to \code{TRUE} in the call to \code{ReadAffy}.} 
    \item{\code{phenoData}:}{Object of class \code{AnnotatedDataFrame}
      containing phenotypic data for the samples.}
    \item{\code{annotation}}{A character string identifying the
      annotation that may be used for the \code{ExpressionSet}
      instance.}
    \item{\code{featureData}}{Object of class \code{AnnotatedDataFrame}
      containing feature-level (e.g., probeset-level) information.}
    \item{\code{experimentData}:}{Object of class "MIAME" containing
      experiment-level information.} 
    \item{\code{notes}:}{Object of class "character" Vector of
      explanatory text }
  }
}
\section{Extends}{
Class \code{"eSet"}, directly.
}
\section{Methods}{
  \describe{
    \item{cdfName}{\code{signature(object = "AffyBatch")}: Obtains the
      cdfName slot.}
    \item{pm<-}{\code{signature(object = "AffyBatch")}: replaces the
      perfect match intensities }
    \item{pm}{\code{signature(object = "AffyBatch")}: extracts the pm intensities. }
    \item{mm<-}{\code{signature(object = "AffyBatch")}: replaces the
      mismatch intensities.}
    \item{mm}{\code{signature(object = "AffyBatch")}: extracts the mm intensities. }
    \item{probes}{\code{signature(object = "AffyBatch", which)}: extract the
      perfect match or mismatch probe intensities. Uses which can be "pm"
    and "mm".}
    \item{exprs}{\code{signature(object = "AffyBatch")}: extracts the
      expression matrix.}
    \item{exprs<-}{\code{signature(object = "AffyBatch", value = "matrix")}: replaces the
      expression matrix.}
    \item{se.exprs}{\code{signature(object = "AffyBatch")}: extracts the
      matrix of standard errors of expression values, if available.}
    \item{se.exprs<-}{\code{signature(object = "AffyBatch", value = "matrix")}: replaces the
      matrix of standard errors of expression values.}
    \item{[<-}{\code{signature(x = "AffyBatch")}: replaces subsets. }
    \item{[}{\code{signature(x = "AffyBatch")}: subsets by array.}
    \item{boxplot}{\code{signature(x = "AffyBatch")}:  creates a
      \code{\link{boxplot}s of log base 2 intensities. }
      \item{hist}{\code{signature(x = "AffyBatch")}:  creates a
       plot showing all the histograms of the pm,mm or both data. See
       \code{\link{plot.density}}}
     \item{computeExprSet}{\code{signature(x = "AffyBatch",
	summary.method = "character")}: For each probe set computes an
      expression value using \code{summary.method}. }
    \item{featureNames}{\code{signature(object = "AffyBatch")}: return the
      probe set names also referred to as the Affymetrix IDs. Notice
      that one can not assign \code{featureNames}. You must do this by changing
      the cdfenvs.}
    \item{geneNames}{\code{signature(object="AffyBatch'")}: deprecated,
      use \code{featureNames}}
    \item{getCdfInfo}{\code{signature(object = "AffyBatch")}: retrieve
      the environment that defines the location of probes by probe set. }
    \item{image}{\code{signature(x = "AffyBatch")}: creates an image for
      each sample.}
    \item{indexProbes}{
      \code{signature(object = "AffyBatch", which = "character")}:
      returns a  list with locations of the probes in
      each probe set. The affyID corresponding to the probe set to
      retrieve can be specified in an optional parameter
      \code{genenames}. By default, all the affyIDs are retrieved.
      The names of the elements in the list returned are the affyIDs.
      \code{which} can be "pm", "mm", or "both". If "both" then
      perfect match locations are given followed by mismatch locations.

      \code{signature(object = "AffyBatch", which = "missing")} (i.e.,
      calling \code{indexProbes} without a "which" argument) is the
      same as setting "which" to "pm".
    } 
    \item{intensity<-}{\code{signature(object = "AffyBatch")}: a
      replacement method for the \code{exprs} slot, i.e. the intensities. }
    \item{intensity}{\code{signature(object = "AffyBatch")}: extract the
      \code{exprs} slot, i.e. the intensities. }
    \item{length}{\code{signature(x = "AffyBatch")}: returns the number
      of samples. }
    \item{pmindex}{\code{signature(object = "AffyBatch")}: return the
      location of perfect matches in the intensity matrix.}
    \item{mmindex}{\code{signature(object = "AffyBatch")}: return the
      location of the mismatch intensities. }
    \item{dim}{\code{signature(x = "AffyBatch")}: Row and column dimensions.}
    \item{ncol}{\code{signature(x = "AffyBatch")}: An accessor function
      for \code{ncol}.}
    \item{nrow}{\code{signature(x = "AffyBatch")}: an accessor function
      for \code{nrow}}.}
    \item{normalize}{\code{signature(object = "AffyBatch")}: a method to
      \code{\link{normalize}}. The method accepts an argument
      \code{method}. The default methods is specified in package options
      (see the main vignette).
    }
    \item{normalize.methods}{\code{signature(object = "AffyBatch")}:
      returns the normalization methods defined for this class. See \code{\link{normalize}}.}
    \item{probeNames}{\code{signature(object = "AffyBatch")}: returns
      the probe set associated with each row of the intensity matrix. }
    \item{probeset}{\code{signature(object = "AffyBatch",genenames=NULL,
	locations=NULL)}: Extracts \code{\link[affy:ProbeSet-class]{ProbeSet}} objects related to
      the probe sets given in genenames. If an alternative set of
      locations defining pms and mms a list with those locations should
      be passed via the \code{locations} argument.}
    \item{bg.correct}{\code{signature(object = "AffyBatch",
	method="character")}} applies background correction methods
    defined by method.
    \item{updateObject}{\code{signature(object = "AffyBatch", ...,
	verbose=FALSE)}: update, if necessary, an object of class
      AffyBatch to its current class definition. \code{verbose=TRUE}
      provides details about the conversion process.}
  }
}
\note{This class is better described in the vignette.}
\seealso{  related methods \code{\link{merge.AffyBatch}},
  \code{\link{pairs.AffyBatch}}, and
  \code{\link[Biobase:class.eSet]{eSet}}} 

\examples{
## load example
data(affybatch.example)

## nice print
print(affybatch.example)

pm(affybatch.example)[1:5,]
mm(affybatch.example)[1:5,]

## get indexes for the PM probes for the affyID "A28102_at" 
mypmindex <- pmindex(affybatch.example,"A28102_at")
## same operation using the primitive
mypmindex <- indexProbes(affybatch.example, which="pm", genenames="A28102_at")[[1]]
## get the probe intensities from the index
intensity(affybatch.example)[mypmindex, ]

## load bigger example (try 'help(Dilution)' )
data(affybatch.example)
description(affybatch.example) ##we can also use the methods of eSet
sampleNames(affybatch.example)
abstract(affybatch.example)
}

\keyword{classes}
