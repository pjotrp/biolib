 ## A ProbeSet holds probe values for a probe pairs set(*) accross a batch of experiments.
  ## methods 'express.summary.stat' returns of expression value per experiement in the
  ## batch, and 'bg.correct' does background correction (in some sense... the MM probes
  ## were created to measure unspecific hybridization. People thought that doing
  ## PM - MM would remove background noise. The method 'bg.correct' accepts extra parameters
  ## through '...' (can be used to pass background correction parameters common to different
  ## ProbeSet)
  ##
  ## -
  ## (*) : a probe pair set is the set of probes pairs(**) related to an affyid. Generally a
  ##       a probe pair set has 20 elements.
  ## (**): a probe pair (or atom) is a pair of PM/MM values
  ##

if (debug.affy123) cat("-->initProbeSet\n")

setClass("ProbeSet",
         representation(id="character", pm="matrix", mm="matrix"),
         prototype=list(pm=matrix(), mm=matrix()))

setMethod("show", "ProbeSet",
          function(object) {
            cat("ProbeSet object:\n")
            cat("  id=", object@id, "\n", sep="")
            cat("  pm=", nrow(object@pm), "probes x ", ncol(object@pm), " chips\n")
          })

##DEBUG: what to do with that ?
## --> with what ?

if( is.null(getGeneric("colnames")))
                                        #setGeneric("colnames", function(x, do.NULL, prefix)
  setGeneric("colnames")

##for consistency also use sampleNames
if( is.null(getGeneric("sampleNames")))
  setGeneric("sampleNames", function(object)
             standardGeneric("sampleNames"))
setMethod("sampleNames", "ProbeSet",
          function(object) colnames(object))

setMethod("colnames", signature(x="ProbeSet"),
          function(x ,do.NULL=FALSE, prefix="row") {
            
            cnames<-colnames(pm(x))
            
            if (is.null(cnames)) {
              
              if (do.NULL) {
                warning("No column names for ProbeSet")
              }
              else {
                cnames <- paste(prefix, 1:ncols(x@pm))
              }
              
            }
            return(cnames)
          })

## pm
if( is.null(getGeneric("pm")))
  setGeneric("pm", function(object) standardGeneric("pm"))

setMethod("pm", "ProbeSet", function(object) object@pm)

if( is.null(getGeneric("pm<-")))
  setGeneric("pm<-", function(object, value) standardGeneric("pm<-"))

setReplaceMethod("pm", signature=c("ProbeSet", "matrix"),
                 function(object, value) {
                   if (! all(dim(value) == dim(object@mm)))
                     stop("dimension mismatch between 'pm' and 'mm'")
                   object@pm <- value
                 })

## mm
if( is.null(getGeneric("mm")))
  setGeneric("mm", function(object) standardGeneric("mm"))

setMethod("mm", "ProbeSet", function(object) object@mm)


if( is.null(getGeneric("mm<-")))
  setGeneric("mm<-", function(object, value) standardGeneric("mm<-"))

setReplaceMethod("mm", signature=c("ProbeSet", "matrix"),
                 function(object, value) {
                   if (sum(dim(value) == dim(object@mm)) != 2)
                     stop("dimension mismatch between 'pm' and 'mm'")
                   object@mm <- value
                 })

## method express.summary.stat
if( is.null(getGeneric("express.summary.stat")))
  setGeneric("express.summary.stat", function(x, pmcorrect, summary, ...)
             standardGeneric("express.summary.stat"))

setMethod("express.summary.stat",signature(x="ProbeSet",  pmcorrect="character", summary="character"),
          function(x, pmcorrect, summary, summary.param=list(), pmcorrect.param=list()) {
            
            pmcorrect <- match.arg(pmcorrect, pmcorrect.methods)
            summary  <- match.arg(summary, express.summary.stat.methods)
            
            ## simple for system to let one add background correction methods
            ## relies on naming convention
            pmcorrect.methodname <- paste("pmcorrect.", pmcorrect, sep="")
            summary.methodname <- paste("generateExprVal.method.", summary, sep="")
            
            if (! exists(summary.methodname))
              stop(paste("Unknown method (cannot find function", summary.methodname, ")"))
            if (! exists(pmcorrect.methodname))
              stop(paste("Unknown method (cannot find function", pmcorrect.methodname, ")"))
            
            ## NOTE: this could change...
                                        #m <- do.call(bg.correct, c(alist(x@pm, x@mm), param.bg.correct))
            pm.corrected <- do.call(pmcorrect.methodname, c(alist(x), pmcorrect.param))
            r <- do.call(summary.methodname, c(alist(pm.corrected), summary.param))
            
            ##DEBUG: name stuff to sort
                                        #names(r) <- names(allprobes)
            
            return(r)
          })

if( is.null(getGeneric("barplot")))
  setGeneric("barplot")

setMethod("barplot",signature(height="ProbeSet"),function(height,...) barplot.ProbeSet(height,...))

if( is.null(getGeneric("mas5calls")) )
  setGeneric("mas5calls", function(object,...) standardGeneric("mas5calls"))

setMethod("mas5calls",signature(object="ProbeSet"),
          function(object,...) mas5calls.ProbeSet(object,...))

