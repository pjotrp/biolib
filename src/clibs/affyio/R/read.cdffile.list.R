###
### File: read.cdffile.list.R
###
### Aim: reads full CDF file into R list structure.
###
### History
### Dec 1, 2005 - Initial version
###


read.cdffile.list <- function (filename, cdf.path = getwd()){

  cdf.type <- check.cdf.type(file.path(path.expand(cdf.path),filename))
  if (cdf.type == "xda"){
    .Call("ReadCDFFileIntoRList", file.path(path.expand(cdf.path),
                                            filename), TRUE, PACKAGE = "affyio")
  } else if (cdf.type =="text"){
    .Call("ReadtextCDFFileIntoRList", file.path(path.expand(cdf.path),
                                                filename), TRUE, PACKAGE = "affyio")
  } else {
    stop(paste("File format for",filename,"not recognized."))
  }
}
