###
### File: read.celfile.header.R
###
### Aim: read header contents of a given specified CEL file into
###      an R data structure.
###


read.celfile.header <- function(filename,info=c("basic","full"),verbose=FALSE){
  compress <- FALSE

  info <- match.arg(info)

  if (info == "basic"){
    if (verbose)
      cat("Reading", filename, "to get header information.\n")
    headdetails <- .Call("ReadHeader", filename, PACKAGE="affyio")
    names(headdetails) <- c("cdfName","CEL dimensions")
  } else {
    if (verbose)
      cat("Reading", filename, "to get full header information.\n")
    ### full returns greater detailed information from the header. Exact details differ depending on the file format.
    headdetails <- try(.Call("ReadHeaderDetailed", filename, PACKAGE="affyio"))
    if (is(headdetails, "try-error"))
        stop("Failed to get full header information for ", filename)
    names(headdetails) <- c("cdfName","CEL dimensions","GridCornerUL","GridCornerUR","GridCornerLR","GridCornerLL","DatHeader","Algorithm","AlgorithmParameters","ScanDate")

    if (nchar(headdetails$ScanDate) == 0){
      # try to extract it from the DatHeader
      DatHeaderSplit <- strsplit(headdetails$DatHeader," ")
      Which.Date <- grep("[0-9]*/[0-9]*/[0-9]*",DatHeaderSplit[[1]])
      Which.Time <-  grep("[0-9]*:[0-9]*:[0-9]*",DatHeaderSplit[[1]])
      headdetails$ScanDate <- paste(DatHeaderSplit[[1]][Which.Date],DatHeaderSplit[[1]][Which.Time])
    }
  }
  return(headdetails)
}
