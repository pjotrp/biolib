##this function changes the affymetrix cdf file name to the Bioconductor
##annotation name for that cdf file
## note: we had a hard time finding exact rules to match what is in the
## CEL file with what is in the CDF file
## ex: CEL says 'ecoli' while CDF says 'ecoligenome'
## or: CEL says '' while CDF says hu6800.1sq
cleancdfname <- function(cdfname, addcdf=TRUE) {
  if( !is.character(cdfname) )
                stop(paste("invalid CDF name:", cdfname))
  if ( nchar(cdfname)[1] == 0 )
               stop("supplied cdf name has zero length")

  data(mapCdfName,envir=environment())
  i <- match(cdfname, mapCdfName$inCDF)
  if (is.na(i)) {
    tmp <- tolower(cdfname) #make lower case
    tmp <- gsub("_", "", tmp) #take out underscore
    tmp <- gsub("-", "", tmp) #take out underscore
    tmp <- gsub("\ ", "", tmp) ##take out spaces
    if (addcdf) {
        ## make sure we haven't already added "cdf"
        endsWith <- substr(tmp, nchar(tmp)-2, nchar(tmp))
        if (endsWith != "cdf")
          tmp <- paste(tmp, "cdf", sep="")
    }
  } else {
    tmp <- mapCdfName$inBioC[1]
  }
  return(tmp)
}

##this function gets the cdf from a celfile
whatcdf <- function(filename, compress=getOption("BioC")$affy$compress.cel)
  return(.Call("ReadHeader",as.character(filename),compress, PACKAGE="affyio")[[1]])



