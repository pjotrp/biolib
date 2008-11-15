## computeExprSet:
##   - better reporting of errors
##   - better handling of ids (does not crash any longer when unknown id)
##   - use of the progress bar in Biobase 1.4.4
##   - cleanup of the comments in the code
## indexProbes:
##   - deprecated flag 'xy' removed for good


if (debug.affy123) cat("-->initAffyBatch\n")

## Inherits from Affybatch
## The accessor 'intensity' gets what is in the slot 'exprs'
setClass("AffyBatch",
         representation=representation(
           cdfName="character",
           nrow="numeric",
           ncol="numeric"),
         contains="eSet",
         prototype=prototype(
           new("VersionedBiobase",
               versions=c(classVersion("eSet"), AffyBatch="1.2.0"))))


setMethod("initialize",
          signature(.Object="AffyBatch"),
          ## provide a signature consistent with the new defintion, but that picks up the (implicit) old
          function(.Object,
                   cdfName="", nrow=0, ncol=0,
                   phenoData, featureData,
                   experimentData=new("MIAME"),
                   annotation=character(0),
                   exprs=matrix(numeric(0), nrow=nrow, ncol=ncol),
                   ## se.exprs
                   ...) {
              .Object@cdfName <- cdfName
              .Object@nrow <- nrow
              .Object@ncol <- ncol
              dots <- list(...)
              ## remove reporterInfo, description, notes from '...'
              if ("reporterInfo" %in% names(dots)) {
                  if (missing(featureData)) {
                      if (!is.null(dots[["reporterInfo"]])) {
                          if (is(dots[["reporterInfo"]], "data.frame"))
                            featureData <- new("AnnotatedDataFrame", data=dots[["reporterInfo"]])
                          else {
                              warning("trying to convert reporterInfo (class '", class(dots[["reporterInfo"]]),
                                      "') to featureData (class 'AnnotatedDataFrame')",
                                      immediate.=TRUE)
                              featureData <- as(dots[["reporterInfo"]], "AnnotatedDataFrame")
                          }
                      } else stop("use 'featureData' rather than 'reporterInfo' for feature covariates")
                  }
              }
              if ("description" %in% names(dots)) {
                  if (missing(experimentData)) experimentData <- dots[["description"]]
                  else stop("use 'experimentData' rather than 'description' for experiment description")
              }
              if ("notes" %in% names(dots)) {
##                   warning("addding 'notes' to 'experimentData'")
                  notes(experimentData) <- c(notes(experimentData), dots[["notes"]])
              }
              dots <- dots[!names(dots) %in% c("reporterInfo", "description", "notes")]
              ## update phenoData to AnnotatedDataFrame, if necessary
              assayData <- do.call("assayDataNew",
                                   c(list(exprs=exprs), dots))
              if (missing(phenoData) || is.null(phenoData))
                phenoData <- annotatedDataFrameFrom(assayData, byrow=FALSE)
              else if (!is(phenoData, "AnnotatedDataFrame"))
                phenoData <- as(phenoData, "AnnotatedDataFrame")
              if (missing(featureData)) featureData <- annotatedDataFrameFrom(assayData, byrow=TRUE)
              callNextMethod(.Object,
                             assayData=assayData,
                             phenoData=phenoData,
                             featureData=featureData,
                             experimentData=experimentData,
                             annotation=annotation)
          })

setMethod("updateObject",
          signature(object="AffyBatch"),
          function(object, ..., verbose=FALSE) {
              if (verbose) message("updateObject(object = 'AffyBatch'")
              if (isVersioned(object) && isCurrent(object)["AffyBatch"])
                return(callNextMethod())
              if (!isVersioned(object) || is.null(classVersion(object)[["AffyBatch"]])) {
                  exprs <- slot(object, "exprs")
                  se.exprs <- slot(object, "se.exprs")
                  if (!all(dim(se.exprs) == dim(exprs))) {
                      if (!all(dim(se.exprs)==0))
                        warning("removing 'se.exprs' with dimensions different from 'exprs'")
                      se.exprs <- NULL
                  }
                  if ("reporterInfo" %in% names(attributes(object)) &&
                      any(dim(slot(object, "reporterInfo"))!=0))
                    warning("reporterInfo data not transfered to 'AffyBatch' object")
                  experimentData=updateObject(slot(object, "description"))
                  if ("notes" %in% names(attributes(object)) &&
                      length(slot(object, "notes"))!=0) {
                      warning("adding 'notes' to 'experimentData'")
                      notes(experimentData) <- c(notes(experimentData), object@notes)
                  }
                  if (!is.null(se.exprs))
                    new("AffyBatch",
                        phenoData=as(slot(object, "phenoData"), "AnnotatedDataFrame"),
                        experimentData=experimentData,
                        annotation=slot(object, "annotation"),
                        cdfName=slot(object, "cdfName"),
                        nrow=slot(object, "nrow"),
                        ncol=slot(object, "ncol"),
                        exprs=exprs,
                        se.exprs=se.exprs)
                  else
                    new("AffyBatch",
                        phenoData=as(slot(object, "phenoData"), "AnnotatedDataFrame"),
                        experimentData=experimentData,
                        annotation=slot(object, "annotation"),
                        cdfName=slot(object, "cdfName"),
                        nrow=slot(object, "nrow"),
                        ncol=slot(object, "ncol"),
                        exprs=exprs)
              } else if (!isCurrent(object)[["AffyBatch"]]) {
                  ## remove empty se.exprs, introduced in class version 1.2.0
                  se.exprs <- assayData(object)[["se.exprs"]]
                  if (!is.null(se.exprs) && all(is.na(se.exprs))) {
                      message("removing 'se.exprs' with all NA values")
                      se.exprs(object) <- NULL
                  }
                  object <- callNextMethod()
                  classVersion(object)["AffyBatch"] <- classVersion("AffyBatch")["AffyBatch"]
                  object
              } else object
          })

#######################################################
### accessors
#######################################################

if (debug.affy123) cat("--->accessors\n")

setMethod("exprs",
          signature(object="AffyBatch"),
          function(object) assayData(object)[["exprs"]])

setReplaceMethod("exprs",
          signature(object="AffyBatch"),
          function(object, value) assayDataElementReplace(object, "exprs", value))

setMethod("se.exprs",
          signature(object="AffyBatch"),
          function(object) {
              obj <- assayData(object)[["se.exprs"]]
              if (is.null(obj))
                new("matrix")
              else
                obj
          })


setReplaceMethod("se.exprs",
          signature(object="AffyBatch"),
          function(object, value) assayDataElementReplace(object, "se.exprs", value))

if (is.null(getGeneric("cdfName")))
    setGeneric("cdfName", function(object)
               standardGeneric("cdfName"))

setMethod("cdfName", "AffyBatch", function(object)
          object@cdfName)

##intensity
setGeneric("intensity", function(object)
           standardGeneric("intensity"))

setMethod("intensity", signature(object="AffyBatch"),
          function(object) assayData(object)[["exprs"]])

setGeneric("intensity<-", function(object, value)
           standardGeneric("intensity<-"))

setReplaceMethod("intensity", signature(object="AffyBatch"),
                 function(object, value){
                     assayDataElementReplace(object, "exprs", value)
                 })

##for now, there is no accessor for se.exprs. we could use this to store
##sd, but if no one uses it... why do it

setMethod("length",signature(x="AffyBatch"),
          function(x) ncol(exprs(x))) ##RI: assumes matrices

setMethod("dim",
          signature=signature(x="AffyBatch"),
          function(x) c(x@nrow, x@ncol))

#######################################################
### methods
#######################################################

setMethod("featureNames",
          signature=signature(object="AffyBatch"),
          function(object) {
              cdf.envir <- getCdfInfo(object)
              ls(env=cdf.envir)
          })

setReplaceMethod("featureNames",
                 signature=signature(
                   object="AffyBatch",
                   value="ANY"),
                 function(object, value)
                 stop("Cannot change featureNames of AffyBatch"))

##geneNames method
if (debug.affy123) cat("--->geneNames\n")

if( is.null(getGeneric("geneNames") ))
  setGeneric("geneNames", function(object)
             standardGeneric("geneNames"))

setMethod("geneNames",signature("AffyBatch"),
            function(object){
              cdf.envir <- getCdfInfo(object)
              return(ls(env=cdf.envir))
            })

setReplaceMethod("geneNames", "AffyBatch", function(object, value){
  stop("This operation is not permitted.\nTo change geneNames change the cdf environment.\n")
})

##show method
if (debug.affy123) cat("--->show\n")

setMethod("show", "AffyBatch",
          function(object) {
              if (!isVersioned(object) ||
                  classVersion(object)["AffyBatch"] < "1.1.0")
                stop("AffyBatch out-of-date; use 'updateObject(<AffyBatch>)'",
                     call.=FALSE)
              if (!isCurrent(object)['AffyBatch'])
                message("AffyBatch out-of-date; consider 'updateObject(<AffyBatch>)'")
              ## Location from cdf env
              cdf.env <-
                tryCatch(getCdfInfo(object),
                         error=function(err) {
                             warning("missing cdf environment! in show(AffyBatch)", call.=FALSE)
                             NULL
                         })
              num.ids <-
                if (!is.null(cdf.env)) length(ls(env=cdf.env))
                else num.ids <- "???"

              cat("AffyBatch object\n")
              cat("size of arrays=", nrow(object), "x", ncol(object),
                  " features (", object.size(object) %/% 1024, " kb)\n", sep="")
              cat("cdf=", object@cdfName,
                  " (", num.ids, " affyids)\n",
                  sep="")
              cat("number of samples=",length(object),"\n",sep="")
              cat("number of genes=", length(featureNames(object)), "\n",sep="")
              cat("annotation=",object@annotation,"\n",sep="")
              if(length(notes(object))>0)
                cat("notes=",paste(notes(object),collapse="\n\t"), "\n")
          })


# if (is.null(getGeneric("index2xy"))) {
#   setGeneric("indexProbes", function(object, which, ...)
#              standardGeneric("indexProbes"))
# }


## indexProbes
if( is.null(getGeneric("indexProbes")))
  setGeneric("indexProbes", function(object, which, ...)
             standardGeneric("indexProbes"))

setMethod("indexProbes",
          signature=c(object="AffyBatch", which="missing"),
          function(object, which, ...) indexProbes(object, which="pm", ...))

setMethod("indexProbes", signature("AffyBatch", which="character"),
          function(object, which=c("pm", "mm","both"),
                   genenames=NULL) {

            which <- match.arg(which)

            i.probes <- match(which, c("pm", "mm", "both"))
            ## i.probes will know if "[,1]" or "[,2]"
            ## if both then [,c(1,2)]
            if(i.probes==3) i.probes=c(1,2)

            envir <- getCdfInfo(object)

            if(is.null(genenames))
              genenames <- ls(envir )

            ## note: the variable name genenames could be confusing (the same gene can be
            ## found in several affyid (ex: the 3' and 5' controls)

            ans <-  mget(genenames, envir, ifnotfound=NA)

            ## this kind of thing could be included in 'mget' as
            ## an extra feature. A function could be specified to
            ## process what is 'multi'-get on the fly
            for (i in seq(along=ans)) {

              if ( is.na(ans[[i]][1]) )
                next

              ##as.vector cause it might be a matrix if both
              tmp <- as.vector(ans[[i]][, i.probes])

              ans[[i]] <- tmp
            }

            return(ans)
          })


  ##pmindex method
if( is.null(getGeneric("pmindex")))
  setGeneric("pmindex", function(object,...)
             standardGeneric("pmindex"))

##wrapper
setMethod("pmindex", "AffyBatch",
            function(object, genenames=NULL)
          indexProbes(object, "pm", genenames=genenames))

  ##mmindex method
if( is.null(getGeneric("mmindex")))
  setGeneric("mmindex", function(object,...)
             standardGeneric("mmindex"))

##wrapper
setMethod("mmindex", "AffyBatch",
          function(object,genenames=NULL)
          indexProbes(object, "mm", genenames=genenames))


##probeNames method
if( is.null(getGeneric("probeNames")))
  setGeneric("probeNames", function(object, ...)
             standardGeneric("probeNames"))

setMethod("probeNames","AffyBatch",
          function(object, genenames=NULL, mm=FALSE){
            if(mm) Index <- mmindex(object,genenames)
            else Index <- pmindex(object,genenames)
            reps <- unlist(lapply(Index,length),use.names=FALSE)
            rep(names(Index),reps)
          })


if( is.null(getGeneric("probes")) )
  setGeneric("probes", function(object, ...)
             standardGeneric("probes"))

setMethod("probes", signature("AffyBatch"),
          function(object, which=c("pm", "mm"),
                   genenames=NULL, LISTRUE=FALSE, drop=FALSE){

            which <- match.arg(which)

            index <- indexProbes(object, which, genenames)

            if(LISTRUE)
              ans <- lapply(index, function(i) exprs(object)[i, ,drop=drop])
            else{
              index <- unlist(index)
              ans <- exprs(object)[index, ,drop=drop]
              colnames(ans) <- sampleNames(object)
              rownames(ans) <- names(index)
            }

            return(ans)
          })

##pm method
if( is.null(getGeneric("pm") ))
  setGeneric("pm", function(object, ...)
             standardGeneric("pm"))

setMethod("pm","AffyBatch",
          function(object, genenames=NULL, LISTRUE=FALSE){
            if(is.null(genenames) & !LISTRUE){
              cdfname <- getCdfInfo(object)
              psets<- as.list(cdfname)
              psets<- psets[order(names(psets))]
              index <-unlist(sapply(psets, function(x) x[,1]),use.names=FALSE)
              return(exprs(object)[index,,drop=FALSE])
            }
            else{
              return(probes(object, "pm", genenames, LISTRUE=LISTRUE))
            }
          })

if( is.null(getGeneric("pm<-") ))
  setGeneric("pm<-", function(object, value)
             standardGeneric("pm<-"))

setReplaceMethod("pm", "AffyBatch", function(object, value){
  Dimnames <- dimnames(exprs(object))
  cdfname <- getCdfInfo(object)
  psets<- as.list(cdfname)
  psets<- psets[order(names(psets))]
  pmIndex <-unlist(sapply(psets, function(x) x[,1]),use.names=FALSE)

  exprs(object)[pmIndex,] <- value
  dimnames(exprs(object)) <- Dimnames
  object
})



##mm method
if( is.null(getGeneric("mm") ))
  setGeneric("mm", function(object, ...)
             standardGeneric("mm"))

setMethod("mm",signature("AffyBatch"),
          function(object, genenames=NULL, LISTRUE=FALSE){
            if(is.null(genenames) & !LISTRUE){
              cdfname <- getCdfInfo(object)
              psets<- as.list(cdfname)
              psets<- psets[order(names(psets))]
              index <-unlist(sapply(psets, function(x) x[,2]),use.names=FALSE)
              return(exprs(object)[index,,drop=FALSE])
            }
            else{
              probes(object, "mm", genenames, LISTRUE=LISTRUE)
            }
          })


if( is.null(getGeneric("mm<-") ))
  setGeneric("mm<-", function(object, value)
             standardGeneric("mm<-"))

setReplaceMethod("mm", "AffyBatch", function(object, value){
  Dimnames <- dimnames(exprs(object))
  cdfname <- getCdfInfo(object)
  psets<- as.list(cdfname)
  psets<- psets[order(names(psets))]
  mmIndex <-unlist(sapply(psets, function(x) x[,2]),use.names=FALSE)
  exprs(object)[mmIndex,] <- value
  dimnames(exprs(object)) <- Dimnames
  object
})

###probeset
if( is.null(getGeneric("probeset") ))
  setGeneric("probeset", function(object, ...)
             standardGeneric("probeset"))

setMethod("probeset", "AffyBatch", function(object, genenames=NULL,
                                            locations=NULL){
  oldoptions <- getOption("BioC")

  if(is.null(locations)) ##use info in cdf
    envir <- getCdfInfo(object)
  else{
    ##if the user gives a list of locations let them use that as enviromnet
    envir <- new.env()
    multiassign(names(locations), locations, envir)
    object@cdfName <- "envir"
    newoptions <- oldoptions
    newoptions$affy$probesloc[[1]]$what <- "environment"
    newoptions$affy$probesloc[[1]]$where <- parent.env(envir)
    options("BioC"=newoptions)
  }
  if(is.null(genenames))
    genenames <- ls(envir)

  p.pps <- vector("list", length(genenames))
  names(p.pps) <- genenames

  for (i in seq(along=genenames)) {

    i.pm <- indexProbes(object, "pm", genenames[i])[[1]]
    if (is.na(i.pm)[1])
      intensity.pm <- matrix()
    else
      intensity.pm <- intensity(object)[i.pm, , drop=FALSE]

    i.mm <- indexProbes(object, "mm", genenames[i])[[1]]
    if (is.na(i.mm)[1])
      intensity.mm <- matrix()
    else
      intensity.mm <- intensity(object)[i.mm, , drop=FALSE]

    p.pps[[i]] <- new("ProbeSet", id = genenames[i], pm = intensity.pm, mm = intensity.mm)
  }

  options("BioC"=oldoptions)
  return(p.pps)
})

if (debug.affy123) cat("--->[[\n")


##[[: no more [[, because no more cel class
# setMethod("[[", "AffyBatch",
#           function(x, i, j, ...) { ##no need for j
#             return(new("Cel",
#                        intensity = matrix(intensity(x)[, i], ncol(x), nrow(x)),
#                        name = sampleNames(x)[i],
#                        cdfName = x@cdfName,
#                        history = description(x)@preprocessing))
#           })

##[[ we need replacement that takes an entry by the Cel in value

##[ subseting. can only happen by sample. for now not by gene
setMethod("[", "AffyBatch", function(x, i, j,..., drop=FALSE) {
  if( !missing(i) & missing(j)) {
    warning("The use of abatch[i,] and abatch[i] is decrepit. Please us abatch[,i] instead.\n")
    phenoData(x) <- phenoData(x)[i, , ..., drop=FALSE]
    intensity(x) <- intensity(x)[ ,i, ..., drop=FALSE]
    if (! identical(se.exprs(x), new("matrix")))  {
      se.exprs(x) <- se.exprs(x)[ ,i, ..., drop=FALSE]
    }
  }

  if( !missing(j)) {
    phenoData(x) <- phenoData(x)[j, , ..., drop=FALSE]
    intensity(x) <- intensity(x)[ ,j, ..., drop=FALSE]
    if (! identical(se.exprs(x), new("matrix"))) { 
      se.exprs(x) <- se.exprs(x)[ ,j, ..., drop=FALSE]
    }
  }

  return(x)
})

setReplaceMethod("[", "AffyBatch", function(x, i, j,..., value) {
  phenoData(x)[i,, ...] <- phenoData(value)[i, , ..., drop=FALSE]
  intensity(x)[,i]      <- intensity(value)[ ,i,... , drop=FALSE]
  return(x)
})


## --- bg.correct

if (debug.affy123) cat("--->bg.correct\n")

if( is.null(getGeneric("bg.correct") ))
  setGeneric("bg.correct", function(object, method, ...)
             standardGeneric("bg.correct"))

setMethod("bg.correct", signature(object="AffyBatch", method="character"),
          function(object, method=getOption("BioC")$affy$bgcorrect.method, ...) {

            ## simple for system to let one add background correction methods
            ## relies on naming convention

            method <- match.arg(method, bgcorrect.methods)

            methodname <- paste("bg.correct.", method, sep="")

            if (! exists(methodname))
              stop(paste("Unknown method (cannot find function", methodname, ")"))

            r <- do.call(methodname, alist(object, ...))

            return(r)
          })


## --- normalize.methods
if( is.null(getGeneric("normalize.methods")))
  setGeneric("normalize.methods", function(object)
             standardGeneric("normalize.methods"))


setMethod("normalize.methods", signature(object="AffyBatch"),
          function(object) {
            normalize.AffyBatch.methods
          })

  ## ---normalize
if (is.null(getGeneric("normalize")))
  setGeneric("normalize", function(object, ...) standardGeneric("normalize"))

  setMethod("normalize", signature(object="AffyBatch"),
            function(object, method=getOption("BioC")$affy$normalize.method, ...) {
              method <- match.arg(method, normalize.AffyBatch.methods)
              if (is.na(method))
                stop("unknown method")
              method <- paste("normalize.AffyBatch", method, sep=".")
              object <- do.call(method, alist(object, ...))
              ## collect info in the attribute "normalization"
              preproc <- c(description(object)@preprocessing,
                           list(normalization = attr(object, "normalization")))
              attr(object, "normalization") <- NULL
              ## and store it in MIAME
              MIAME <- description(object)
              MIAME@preprocessing <- preproc
              description(object) <- MIAME
              ##
              return(object)
            })


## --- expression value computation
if (debug.affy123) cat("--->computeExprSet\n")
if( is.null(getGeneric("computeExprSet")))
  setGeneric("computeExprSet",
             function(x, pmcorrect.method, summary.method, ...)
             standardGeneric("computeExprSet"))

setMethod("computeExprSet", signature(x="AffyBatch", pmcorrect.method="character", summary.method="character"),
          function(x, pmcorrect.method, summary.method, ids=NULL,
                   verbose=TRUE, summary.param=list(),
                   pmcorrect.param=list())
          {

            pmcorrect.method<- match.arg(pmcorrect.method, pmcorrect.methods)
            summary.method <- match.arg(summary.method, express.summary.stat.methods)

            ids <- unname(ids)
            
            n <- length(x)

            ## if 'ids' is NULL compute for all ids
            if (is.null(ids))
              ids <- featureNames(x)

            m <- length(ids)
            pps.warnings <- vector("list", length=m)

            ## cheap trick to (try to) save time
            c.pps <- new("ProbeSet",
                         pm=matrix(),
                         mm=matrix())

            ## matrix to hold expression values
            exp.mat <- matrix(NA, m, n)
            se.mat <- matrix(NA, m, n)

            if (verbose) {
              cat(m, "ids to be processed\n")
              countprogress <- 0
            }

            ## loop over the ids
            mycall <- as.call(c(getMethod("express.summary.stat",
                                          signature=c("ProbeSet","character", "character")),
                                list(c.pps, pmcorrect=pmcorrect.method, summary=summary.method,
                                     summary.param=summary.param, pmcorrect.param=pmcorrect.param))
                              )
            ##only one character cause no more bg correct
            ##bg.correct=bg.method, param.bg.correct=bg.param,

            CDFINFO <- getCdfInfo(x) ##do it once!

            if (verbose) {
              pbt <- new("ProgressBarText", length(ids), barsteps = as.integer(20))
              open(pbt)
            }

            for (i in seq(along=ids)) {

              if (verbose) {
                update(pbt)
              }

              id <- ids[i]

              if (! exists(id, envir=CDFINFO)) {
                pps.warnings[[i]] <- paste("Unknown id", id)
              } else {
                ## locations for an id
                loc <- get(id, envir=CDFINFO)
                l.pm <- loc[, 1]
                if (ncol(loc) == 2)
                  l.mm <- loc[ ,2]
                else
                  l.mm <- integer()

                np <- length(l.pm)

                ##names are skipped

                c.pps@pm <- intensity(x)[l.pm, , drop=FALSE]
                c.pps@mm <- intensity(x)[l.mm, , drop=FALSE]

                ## generate expression values
                ## (wrapped in a sort of try/catch)
                mycall[[2]] <- c.pps
                ev <- try(eval(mycall), silent = TRUE)
              }
              if (! inherits(ev, "try-error")) {
                exp.mat[i, ] <- ev$exprs
                se.mat[i,] <- ev$se.exprs
              } else {
                pps.warnings[[i]] <- ev[1]
              }

            }

            if (verbose) {
              close(pbt)
            }

            dimnames(exp.mat) <- list(ids, sampleNames(x))
            dimnames(se.mat) <- list(ids, sampleNames(x))
            eset <- new("ExpressionSet",
                        phenoData=phenoData(x),
                        ## featureData picked up from exprs
                        experimentData=experimentData(x),
                        exprs=exp.mat,
                        se.exprs=se.mat,
                        annotation=annotation(x))

            attr(eset, "pps.warnings") <- pps.warnings
            return(eset)
          })


##some methods i was asked to add

if( is.null(getGeneric("image")))
  setGeneric("image")

setMethod("image",signature(x="AffyBatch"),
          function(x, transfo=log, col=gray(c(0:64)/64), xlab="",
            ylab="",type=c("exprs","se.exprs"), main, ...){
            scn <- prod(par("mfrow"))
            ask <- dev.interactive()
            which.plot <- 0

            type <- match.arg(type)

            if (type == "se.exprs" && all(!dim(se.exprs(x)))){
              stop("no se.exprs in object")
            }



            x.pos <- (1:nrow(x)) - (1 + getOption("BioC")$affy$xy.offset)
            y.pos <- (1:ncol(x)) - (1 + getOption("BioC")$affy$xy.offset)

            for(i in 1:length(sampleNames(x))){
              which.plot <- which.plot+1;
              if(trunc((which.plot-1)/scn)==(which.plot-1)/scn && which.plot>1 && ask)  par(ask=TRUE)

              if (type == "exprs"){
                m <- exprs(x)[,i]
              } else {
                m <- se.exprs(x)[,i]
              }


              if (is.function(transfo)) {
                m <- transfo(m)
              }
              m <- as.matrix(rev(as.data.frame(matrix(m, nrow=length(x.pos), ncol=length(y.pos)))))
              if( missing(main) ){
                main.cur=sampleNames(x)[i]
              } else {
                main.cur <- main
              }
              image(x.pos, y.pos, m,
                    col=col, main=main.cur,
                    xlab=xlab, ylab=ylab,,xaxt='n',
                      yaxt='n', ...)
              par(ask=FALSE)
            }
          })


###boxplot
if( is.null(getGeneric("boxplot")))
  setGeneric("boxplot")

##some special handling of main is needed
setMethod("boxplot",signature(x="AffyBatch"),
          function(x, which="both", range=0, main, ...){
            tmp <- description(x)
            if( missing(main) && (is(tmp, "MIAME")) )
                main <- tmp@title

            tmp <- unlist(indexProbes(x,which))
            tmp <- tmp[seq(1,length(tmp),len=5000)]

            boxplot(data.frame(log2(intensity(x)[tmp,])), main=main,
                      range=range, ...)
          })

###hist
if (debug.affy123) cat("--->hist\n")

if( is.null(getGeneric("hist")) )
  setGeneric("hist")

setMethod("hist",signature(x="AffyBatch"),
    function(x,...) plotDensity.AffyBatch(x,...))


if( is.null(getGeneric("mas5calls")) )
  setGeneric("mas5calls", function(object,...) standardGeneric("mas5calls"))

setMethod("mas5calls",signature(object="AffyBatch"),
          function(object,...) mas5calls.AffyBatch(object,...))


##like for ExpressionSet

"$.AffyBatch" <- function(affybatch, val)
    (pData(affybatch))[[as.character(val)]]

