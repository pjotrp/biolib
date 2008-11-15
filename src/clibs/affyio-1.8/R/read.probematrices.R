###
### File: read.probematrices.R
###
### Aim: read in PM or MM or both probe intensities into a list of
###       of matrices where the probes for particular probesets are
###       contiguous in the returned matrix
###       Each Matrix has probes in rows and arrays in columns
###
### Copyright (C) 2005     B. M. Bolstad
###
### History
### Nov 30, 2005 - Initial version
###


read.celfile.probeintensity.matrices <- function(filenames, cdfInfo, rm.mask=FALSE, rm.outliers=FALSE, rm.extra=FALSE, verbose=FALSE, which= c("pm","mm","both")){
  which <- match.arg(which)

  filenames <- as.character(filenames)
  if (verbose)
    cat("Reading", filenames[1], "to get header information.\n")
  headdetails <- .Call("ReadHeader", filenames[1], PACKAGE="affyio")
  dim.intensity <- headdetails[[2]]
  ref.cdfName <- headdetails[[1]]
  
  .Call("read_probeintensities", filenames,
        rm.mask, rm.outliers, rm.extra, ref.cdfName,
        dim.intensity, verbose, cdfInfo,which, PACKAGE="affyio")
}
