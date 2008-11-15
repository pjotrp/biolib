###
### file: read.celfile.R
###
### aim: read entire contents of a single given specified CEL file into
###      an R data structure.



read.celfile <- function(filename,intensity.means.only=FALSE){
 return(.Call("R_read_cel_file",filename,intensity.means.only,PACKAGE="affyio"))
}
