expresso <- function(afbatch,
                     ## --
                     bg.correct=TRUE,
                     bgcorrect.method = NULL,
                     bgcorrect.param = list(),
                     ## --
                     normalize = TRUE,
                     normalize.method = NULL,
                     normalize.param=list(),
                     ## --
                     pmcorrect.method = NULL,
                     pmcorrect.param = list(),
                     ## --
                     summary.method = NULL,
                     summary.param = list(),
                     summary.subset = NULL,
                     ## ---
                     verbose = TRUE,
                     widget = FALSE
                     ) {
    # JZ added this function
    setCorrections <- function(){
        bioc.opt <- getOption("BioC")
        if(bg.correct){
            if(is.null(bgcorrect.method)){
                BGMethods <- bgcorrect.methods
            }else{
                BGMethods <- bgcorrect.method
            }
        }else{
            BGMethods <- "None"
        }
        if(normalize){
            if(is.null(normalize.method)){
                normMethods <- normalize.methods(afbatch)
            }else{
                normMethods <- normalize.method   ## was normalizer.method, but think this is typo (BMB)
            }
        }else{
            normMethods <- "None"
        }
        # Default for this one may not be correct
        if(is.null(pmcorrect.method)){
            PMMethods <- pmcorrect.methods
        }else{
            PMMethods <- pmcorrect.method
        }
        # Default for this one may not be correct
        if(is.null(summary.method)){
            expMethods <- generateExprSet.methods

        }else{
            expMethods <- summary.method
        }

        corrections <- expressoWidget(BGMethods, normMethods, PMMethods,
                           expMethods, bioc.opt$affy$bgcorrect.method,
                                      bioc.opt$affy$normalize.method,
                                      bioc.opt$affy$pmcorrect.method,
                                      bioc.opt$affy$summary.method)
        if(!is.null(corrections)){
            if(corrections[["BG"]] != "None"){
                bgcorrect.method <<- corrections[["BG"]]
            }
            if(corrections[["NORM"]] != "None"){
                normalize.method <<- corrections[["NORM"]]
            }
            if(corrections[["PM"]] != "None"){
                pmcorrect.method <<- corrections[["PM"]]
            }
            if(corrections[["EXP"]] != "None"){
                summary.method <<- corrections[["EXP"]]
            }
        }else{
            stop("Aborted by user")
        }
    }

  if (widget) {
    require(tkWidgets) || stop("library tkWidgets could not be found !")
  }

  nchips <- length(afbatch)

  ###background stuff must be added before normalization!

  if(widget){
      setCorrections()
  }

  ## -- summary of what will be done
  if (verbose) {
    if (bg.correct){
      cat("background correction:", bgcorrect.method, "\n")
    }
    if (normalize) {
      cat("normalization:", normalize.method, "\n")
    }
    cat("PM/MM correction :", pmcorrect.method, "\n")
    cat("expression values:", summary.method, "\n")
  }


  ## -- background correct (if needed)
  if (bg.correct) {

    if (verbose)
      cat("background correcting...")

    afbatch <- do.call("bg.correct", c(alist(afbatch, method=bgcorrect.method), bgcorrect.param))

    if (verbose)
      cat("done.\n")
  }

  ## -- normalize (if wished)
  if (normalize) {

    if (verbose)
      cat("normalizing...")

    afbatch <- do.call("normalize",
                       c(alist(afbatch, normalize.method), normalize.param))

    if (verbose)
      cat("done.\n")
  }

  eset <- computeExprSet(afbatch,
                         summary.method=summary.method, pmcorrect.method= pmcorrect.method,
                         ids=summary.subset,
                         summary.param=summary.param, pmcorrect.param=pmcorrect.param)

  return(eset)
}



