.initNormalize <- function(where, all.affy) {
  if (debug.affy123) cat("-->detecting normalization methods from naming convention\n")

  ## this could move into the respective methods of AffyBatch later

  start <- nchar("normalize.AffyBatch.")
  assign("normalize.AffyBatch.methods",
         substr(all.affy[grep("normalize\\.AffyBatch\\.*", all.affy)], start+1, 100),
         envir=as.environment(where))
}

.initExpression <- function(where, all.affy) {
  if (debug.affy123) cat("-->detecting expression value methods from naming convention\n")

  ## the first one is deprecated (well... "should be"...)
  assign("generateExprSet.methods",
         substr(all.affy[grep("generateExprVal\\.method\\.*", all.affy)], 24,100),
         envir=as.environment(where))
  assign("express.summary.stat.methods",
         substr(all.affy[grep("generateExprVal\\.method\\.*", all.affy)], 24,100),
         envir=as.environment(where))
}

.initBackgroundCorrect <- function(where, all.affy) {
  if (debug.affy123) cat("-->detecting background correction methods from naming convention\n")
  ##assign("bg.correct.methods",
  ##       substr(ls(where)[grep("bg.correct\\.*", ls(where))], 12,100),
  ##       envir=as.environment(where))
  start <- nchar("bg.correct.")
  assign("bgcorrect.methods",
         substr(all.affy[grep("bg\\.correct\\.", all.affy)], start+1, 100),
         envir=as.environment(where))
       }

.initPmCorrect <- function(where, all.affy) {
  if (debug.affy123) cat("-->detecting pm correction methods from naming convention\n")
  start <- nchar("pmcorrect.")
  assign("pmcorrect.methods",
         substr(all.affy[grep("pmcorrect\\.*", all.affy)], start+1, 100),
         envir=as.environment(where))
}

##.initMapCdfName <- function(where) {
##  filepath <- system.file("data/apCdfName.rda" package="affy")
##  load(filepath, envir=as.environment(where))
##}

.setAffyOptions <- function(affy.opt=NA) {

  if (! any(is.na(affy.opt))) {
    if (class(affy.opt) != "BioCPkg")
      stop("obviously invalid package options !")

    BioC <- getOption("BioC")
    BioC$affy <- affy.opt
    options("BioC"=BioC)
    return()
  }

  ## add affy specific options
  ## (not unlike what is done in 'Biobase')
  if (is.null(getOption("BioC"))) {
    BioC <- list()
    class(BioC) <- "BioCOptions"
    options("BioC"=BioC)
  }

  probesloc.first <- list(what="environment", where=.GlobalEnv)
  probesloc.second <- list(what="libPath", where=NULL)
  probesloc.third <- list(what="data", where="affy")
  probesloc.fourth <- list(what="bioC", where=.libPaths()[1])


  ## default for the methods
  bgcorrect.method <- "mas"
  normalize.method <- "quantiles"
  pmcorrect.method <- "pmonly"
  summary.method <- "liwong"

  affy.opt <- list(compress.cdf=FALSE, compress.cel=FALSE,
                   use.widgets=FALSE,
                   probesloc = list(probesloc.first, probesloc.second,
                   probesloc.third, probesloc.fourth),
                   bgcorrect.method = bgcorrect.method,
                   normalize.method = normalize.method,
                   pmcorrect.method = pmcorrect.method,
                   summary.method = summary.method,
                   xy.offset = 0 ## this one is for temporary compatibility
                   ) 

  class(affy.opt) <- "BioCPkg"

  BioC <- getOption("BioC")
  BioC$affy <- affy.opt
  options("BioC"=BioC)
  ## ---
}

.First.lib <- function(libname, pkgname) {
    
  where <- match(paste("package:", pkgname, sep=""), search())
  all.affy <- ls(where)
 message <- FALSE

  if (message) {
    cat(rep("*",13),"\n",sep="")
    cat("affy: development version\n")
    cat(rep("*",13),"\n",sep="")
    cat(rep("*",13),"\n",sep="")
    cat("update versions of the required packages if necessary.\n")
    cat(rep("*",13),"\n",sep="")
  }

  library.dynam("affy", pkgname, libname)

  ##.initMapCdfName(match(paste("package:", pkgname, sep=""), search()))
  
  .initNormalize(match(paste("package:", pkgname, sep=""), search()), all.affy)
  .initExpression(match(paste("package:", pkgname, sep=""), search()), all.affy)
  .initBackgroundCorrect(match(paste("package:", pkgname, sep=""), search()), all.affy)
  .initPmCorrect(match(paste("package:", pkgname, sep=""), search()), all.affy)

  .setAffyOptions()

  cacheMetaData(as.environment(where))

    if(.Platform$OS.type == "windows" && require(Biobase) && interactive()
        && .Platform$GUI ==  "Rgui"){
        addVigs2WinMenu("affy")
    }



}





