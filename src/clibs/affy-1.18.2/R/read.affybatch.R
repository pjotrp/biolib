#############################################################
##
## read.affybatch.R
##
## Adapted by B. M. Bolstad from read.affybatch in the affy
## package version 1.2.  The goal is a faster, less memory hungry
## ReadAffy. To do this we will shunt more work off to
## the c code.
##
## History
## Jun 13-15 Intial version
## Jun 16    Verbose flag passed to C routine
## Jun 17    New method for checking header of first cel
##           file.
## Jul 7     Added the function read.probematrix which
##           reads in PM, MM or both into matrices
## Sep 28    changed name from read.affybatch2 to read.affybatch
##           and cleaned up some old commented stuff
## Apr 13, 2004 - fixed problem in read.probematrix
## Nov 15, 2005 - add functionality to read the
##                stddev values into the se.exprs slot (non-default behaviour)
##
## Jan 24, 2006 - JWM: added cdfname to allow for the use of non-standard mappings
## Mar 6, 2006 - change .Call to reference affyio. that is new location for parsing code
## Dec 12, 2006 - added checkCelFiles() to ensure all filenames are celfiles so unintended
##                arguments don't get passed in via ...
##
#############################################################


read.affybatch <- function(..., filenames=character(0),
                           phenoData=new("AnnotatedDataFrame"),
                           description=NULL,
                           notes="",
                           compress = getOption("BioC")$affy$compress.cel,
                           rm.mask = FALSE, rm.outliers=FALSE, rm.extra=FALSE,
                           verbose = FALSE,sd=FALSE, cdfname = NULL) {

  auxnames <- unlist(list(...))
  filenames <- c(filenames, auxnames)
  checkValidFilenames(filenames)

  n <- length(filenames)
  pdata <- pData(phenoData)
  ## try to read sample names form phenoData. if not there use CEL
  ## filenames
  if(dim(pdata)[1] != n) {
    ## if empty pdata filename are samplenames
    warning("Incompatible phenoData object. Created a new one.\n")

    samplenames <- sub("^/?([^/]*/)*", "", filenames, extended=TRUE)
    pdata <- data.frame(sample=1:n, row.names=samplenames)
    phenoData <- new("AnnotatedDataFrame",
                     data=pdata,
                     varMetadata=data.frame(
                       labelDescription="arbitrary numbering",
                       row.names="sample"))
  }
  else samplenames <- rownames(pdata)

  if (is.null(description))
    {
      description <- new("MIAME")
      preproc(description)$filenames <- filenames
      preproc(description)$affyversion <- library(help=affy)$info[[2]][[2]][2]
    }
  if (length(notes)==0) notes(description) <- notes
  ## read the first file to see what we have
  if (verbose) cat(1, "reading",filenames[[1]],"...")

  headdetails <- .Call("ReadHeader",as.character(filenames[[1]]), PACKAGE="affyio")

  ##now we use the length
  dim.intensity <- headdetails[[2]]   ##dim(intensity(cel))
  ##and the cdfname as ref
  ref.cdfName <- headdetails[[1]]   #cel@cdfName

  ## allow for non-standard cdfs
  if(is.null(cdfname))
    cdfname <- ref.cdfName

  if (verbose)
    cat(paste("instantiating an AffyBatch (intensity a ", prod(dim.intensity), "x", length(filenames), " matrix)...", sep=""))

  if (verbose)
    cat("done.\n")

  ## Change sampleNames to be consistent with row.names of phenoData
  ## object

  exprs <- .Call("read_abatch",filenames, rm.mask,
               rm.outliers, rm.extra, ref.cdfName,
               dim.intensity,verbose, PACKAGE="affyio")
  colnames(exprs) <- samplenames
  
  #### this is where the code changes from the original read.affybatch.
  #### what we will do here is read in from the 1st to the nth CEL file
  if (!sd){
    return(new("AffyBatch",
               exprs  = exprs,
               ##se.exprs = array(NaN, dim=dim.sd),
               cdfName    = cdfname,   ##cel@cdfName,
               phenoData  = phenoData,
               nrow       = dim.intensity[1],
               ncol       = dim.intensity[2],
               annotation = cleancdfname(cdfname, addcdf=FALSE),
               description= description,
               notes      = notes))
  } else {
    return(new("AffyBatch",
               exprs  = exprs,
               se.exprs = .Call("read_abatch_stddev",filenames, rm.mask,
                 rm.outliers, rm.extra, ref.cdfName,
                 dim.intensity,verbose, PACKAGE="affyio"),
               cdfName    = cdfname,   ##cel@cdfName,
               phenoData  = phenoData,
               nrow       = dim.intensity[1],
               ncol       = dim.intensity[2],
               annotation = cleancdfname(cdfname, addcdf=FALSE),
               description= description,
               notes      = notes))
  }
}





######################################################################################

read.probematrix <- function(..., filenames = character(0), phenoData = new("AnnotatedDataFrame"),
                             description = NULL, notes = "", compress = getOption("BioC")$affy$compress.cel,
                             rm.mask = FALSE, rm.outliers = FALSE, rm.extra = FALSE, verbose = FALSE,which="pm",
                             cdfname = NULL){

  auxnames <- unlist(list(...))
  filenames <- c(filenames, auxnames)

  which <- match.arg(which,c("pm","mm","both"))

  if (verbose)
    cat(1, "reading", filenames[[1]], "to get header information\n")
  headdetails <- .Call("ReadHeader", as.character(filenames[[1]]), PACKAGE="affyio")
  dim.intensity <- headdetails[[2]]
  ref.cdfName <- headdetails[[1]]
  ## Allow for usage of alternative cdfs
  if(is.null(cdfname))
    Data <- new("AffyBatch", cdfName = ref.cdfName, annotation = cleancdfname(ref.cdfName,addcdf = FALSE))
  else
    Data <- new("AffyBatch", cdfName = cdfname, annotation = cleancdfname(ref.cdfName, addcdf = FALSE))
  
  cdfInfo <- as.list(getCdfInfo(Data))
  cdfInfo <- cdfInfo[order(names(cdfInfo))]


  .Call("read_probeintensities", filenames,
        rm.mask, rm.outliers, rm.extra, ref.cdfName,
        dim.intensity, verbose, cdfInfo,which, PACKAGE="affyio")
}


list.celfiles <-   function(...){
  files <- list.files(...)
  return(files[grep("\\.[cC][eE][lL]\\.gz$|\\.[cC][eE][lL]$", files)])
}

AllButCelsForReadAffy <- function(..., filenames=character(0),
                                  widget=getOption("BioC")$affy$use.widgets,
                                  celfile.path=NULL,
                                  sampleNames=NULL,
                                  phenoData=NULL,
                                  description=NULL){

    ##first figure out filenames
  auxnames <- unlist(as.list(substitute(list(...)))[-1])

  if (widget){
    require(tkWidgets)
    widgetfiles <- fileBrowser(textToShow="Choose CEL files",
                               testFun=hasSuffix("[cC][eE][lL]"))
  }
  else{
    widgetfiles <- character(0)
  }

  if(!is.null(celfile.path)){
    auxnames <- file.path(celfile.path, auxnames)
    filenames <- file.path(celfile.path, filenames)
  }

  filenames <- c(filenames, auxnames, widgetfiles)

  if(length(filenames)==0){
    if(is.null(celfile.path)) celfile.path <- getwd()
    filenames <- list.celfiles(celfile.path,full.names=TRUE)
  }
  if(length(filenames)==0) stop("No cel filennames specified and no cel files in specified directory:",celfile.path,"\n")

  if(is.null(sampleNames)){
    sampleNames <- sub("^/?([^/]*/)*", "", filenames, extended=TRUE)
  }
  else{
    if(length(sampleNames)!=length(filenames)){
      warning("sampleNames not same length as filenames. Using filenames as sampleNames instead\n")
      sampleNames <- sub("^/?([^/]*/)*", "", filenames, extended=TRUE)
    }
  }

  if(is.character(phenoData)) { ##if character read file 
      phenoData <- read.AnnotatedDataFrame(filename=phenoData)
      sampleNames <- sampleNames(phenoData)
  } else{
      if (!is(phenoData, "AnnotatedDataFrame")) {
          pData <- data.frame(sample=seq(1, length(sampleNames)),
                              row.names=sampleNames)
          varMetadata <- data.frame(labelDescription="arbitrary numbering",
                                    row.names=names(pData))
          phenoData <- new("AnnotatedDataFrame",
                           data=pData,
                           varMetadata=varMetadata)
      }
  }


  ##get MIAME information
  if(is.character(description)){
    description <- read.MIAME(filename=description,widget=FALSE)
  }
  else{
      if (! is(description, "MIAME")) {
          description <- new("MIAME")
      }
  }

  ##MIAME stuff
  description@preprocessing$filenames <- filenames
  if(exists("tksn")) description@samples$description <- tksn[,2]
  description@preprocessing$affyversion <- library(help=affy)$info[[2]][[2]][2]

  return(list(filenames   = filenames,
              phenoData   = phenoData,
              sampleNames = sampleNames,
              description = description))
}

###this is user friendly wrapper for read.affybatch
ReadAffy <- function(..., filenames=character(0),
                     widget=getOption("BioC")$affy$use.widgets,
                     compress=getOption("BioC")$affy$compress.cel,
                     celfile.path=NULL,
                     sampleNames=NULL,
                     phenoData=NULL,
                     description=NULL,
                     notes="",
                     rm.mask=FALSE, rm.outliers=FALSE, rm.extra=FALSE,
                     verbose=FALSE,sd=FALSE, cdfname = NULL) {

  l <- AllButCelsForReadAffy(..., filenames=filenames,
                             widget=widget,
                             celfile.path=celfile.path,
                             sampleNames=sampleNames,
                             phenoData=phenoData,
                             description=description)

  ##and now we are ready to read cel files
  ret <- read.affybatch(filenames=l$filenames,
                        phenoData=l$phenoData,
                        description=l$description,
                        notes=notes,
                        compress=compress,
                        rm.mask=rm.mask,
                        rm.outliers=rm.outliers,
                        rm.extra=rm.extra,
                        verbose=verbose,sd=sd,cdfname=cdfname)

  sampleNames(ret) <- l$sampleNames
  return(ret)
}

checkValidFilenames <- function(filenames) {
    ## Returns TRUE if filenames is a character vector containing
    ## paths to files that exist (directories don't count).
    ## A suitable error message is printed via stop() if invalid
    ## file names are encountered.
    if (!is.character(filenames))
      stop(strwrap(paste("file names must be specified using a character",
                         "vector, not a", sQuote(typeof(filenames)))),
           call.=FALSE)

    if (length(filenames) == 0)
      stop("no file names provided")

    if (any(sapply(filenames, nchar) < 1))
      stop("empty file names are not allowed")

    finfo <- file.info(filenames)
    whBad <- sapply(finfo[["isdir"]], function(x) !identical(FALSE, x))
    if (any(whBad)) {
        msg <- paste("the following are not valid files:\n",
                     paste("  ", filenames[whBad], collapse="\n"))
        stop(msg, call.=FALSE)
    }
    TRUE
}





