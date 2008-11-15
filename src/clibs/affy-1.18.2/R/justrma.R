## Sept 11, 2003 - justRMA calls just.rma2
### A user friendly wrapper for just.rma
justRMA <- function(..., filenames=character(0),
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
                    bgversion=2, destructive=FALSE,
                    cdfname = NULL){

  l <- AllButCelsForReadAffy(..., filenames=filenames,
                             widget=widget,
                             celfile.path=celfile.path,
                             sampleNames=sampleNames,
                             phenoData=phenoData,
                             description=description)


  ##and now we are ready to read cel files
 ret<- just.rma(filenames=l$filenames,
                  phenoData=l$phenoData,
                description=l$description,
                notes=notes,
                compress=compress,
                rm.mask=rm.mask,
                rm.outliers=rm.outliers,
                rm.extra=rm.extra,
                verbose=verbose,
                normalize=normalize,
                background=background,
                bgversion=bgversion,
                destructive=destructive,
                cdfname = cdfname)
  sampleNames(ret) <- l$sampleNames
  return(ret)

}




###########################################################################################
#
# this function uses a different parsing routine
# It was added Jul 7, 2003 by B. M. Bolstad
#
###########################################################################################

just.rma <- function(..., filenames=character(0),
                     phenoData=new("AnnotatedDataFrame"),
                     description=NULL,
                     notes="",
                     compress=getOption("BioC")$affy$compress.cel,
                     rm.mask=FALSE, rm.outliers=FALSE, rm.extra=FALSE,
                     verbose=FALSE, background=TRUE, normalize=TRUE,
                     bgversion=2, destructive=FALSE, cdfname = NULL) {

  auxnames <- unlist(list(...))
  filenames <- c(filenames, auxnames)

  checkValidFilenames(filenames)
  
  n <- length(filenames)

  pdata <- pData(phenoData)
  ##try to read sample names form phenoData. if not there use CEL filenames
  if(dim(pdata)[1]!=n){#if empty pdata filename are samplenames
    warning("Incompatible phenoData object. Created a new one.\n")

    samplenames <- gsub("^/?([^/]*/)*", "", unlist(filenames), extended=TRUE	)
    pdata <- data.frame(sample=1:n,row.names=samplenames)
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
      description@preprocessing$filenames <- filenames
      description@preprocessing$affyversion <- library(help=affy)$info[[2]][[2]][2]
    }
  ## read the first file to see what we have
  ##if (verbose) cat(1, "reading",filenames[[1]],"...")

  ## get information from cdf environment

  headdetails <- .Call("ReadHeader", filenames[[1]], compress, PACKAGE="affyio")
  dim.intensity <- headdetails[[2]]
  if(is.null(cdfname))
    cdfname <- headdetails[[1]]
  tmp <- new("AffyBatch",
             cdfName=cdfname,
             annotation=cleancdfname(cdfname, addcdf=FALSE))
  pmIndex <- pmindex(tmp)
  probenames <- rep(names(pmIndex), unlist(lapply(pmIndex,length)))
  pmIndex <- unlist(pmIndex)

  ## read pm data into matrix

  probeintensities <- read.probematrix(filenames=filenames, cdfname = cdfname)

  ##pass matrix of pm values to rma

  ngenes <- length(geneNames(tmp))

  ##background correction
  bg.dens <- function(x){density(x,kernel="epanechnikov",n=2^14)}

  #if(destructive){
    exprs <-
    .Call("rma_c_complete",probeintensities$pm,probenames,ngenes,body(bg.dens),new.env(),normalize,background,bgversion, verbose,
    PACKAGE="affy")
  #}else{
  #  exprs <- .Call("rma_c_complete_copy",probeintensities$pm,probeintensities$pm,probenames,ngenes,body(bg.dens),new.env(),normalize,background,bgversion)
  #}
  colnames(exprs) <- samplenames
  se.exprs <- array(NA, dim(exprs),
                    dimnames=list(rownames(exprs), colnames(exprs)))

  annotation <- annotation(tmp)
  notes(description) <- notes
  new("ExpressionSet",
      phenoData = phenoData,
      annotation = annotation,
      experimentData = description,
      exprs = exprs, se.exprs = se.exprs)
}





