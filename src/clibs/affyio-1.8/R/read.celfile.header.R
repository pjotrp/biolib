


read.celfile.header <- function(filename,info=c("basic","full"),verbose=FALSE){
  compress <- FALSE

  info <- match.arg(info)

  if (info == "basic"){
    if (verbose)
      cat("Reading", filename, "to get header information.\n")
    headdetails <- .Call("ReadHeader", filename, PACKAGE="affyio")
    names(headdetails) <- c("cdfName","CEL dimensions")
    
    return(headdetails)
  } else {
    if (verbose)
      cat("Reading", filename, "to get full header information.\n")
    ### full returns greater detailed information from the header. Exact details differ depending on the file format.
    headdetails <- .Call("ReadHeaderDetailed", filename, PACKAGE="affyio")
    names(headdetails) <- c("cdfName","CEL dimensions","GridCornerUL","GridCornerUR","GridCornerLR","GridCornerLL","DatHeader","Algorithm","AlgorithmParameters")

    return(headdetails)
  }


}
  
