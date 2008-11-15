###
### File: check.cdf.type.R
###
### AIM: return a string giving the file format. Either text, xda or unknown
###      in the case that file format is not known.
###


check.cdf.type <- function(filename){

  if (.Call("CheckCDFtext",filename,PACKAGE="affyio")){
    return("text")
  } else if (.Call("CheckCDFXDA",filename,PACKAGE="affyio")){
    return("xda")
  } else {
    return("unknown")
  }


}
