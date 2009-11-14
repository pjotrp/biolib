debug.affy123 <- FALSE

setClass("ProgressBarText", representation(steps = "integer", barsteps = "integer", internals = "environment"))

setMethod("initialize", "ProgressBarText",
          function(.Object, steps, barsteps = 10, internals = NULL) {
            ##.Object <- callNextMethod()
            if ( ! is.null(internals)) {
              stop("slot 'internals' is for internal use !")
            }
            .Object@barsteps = barsteps
            .Object@internals = new.env()
            assign("milestones.i", as.integer(1), envir=.Object@internals)
            assign("increment", as.integer(1), envir=.Object@internals)
            assign("milestones", as.integer(seq(1, steps, length=barsteps)), envir=.Object@internals)
            assign("i", as.integer(0), envir=.Object@internals)
            return(.Object)
          })

setMethod("open", "ProgressBarText",
          function(con, header = TRUE) {
            if (header) {
              cat("|", paste(rep(" ", con@barsteps), collapse=""), "|\n", sep="")
            }
            cat("|")
            increment <- get("increment", con@internals)
            milestones.i <- get("milestones.i", con@internals)
            milestones <- get("milestones", con@internals)
            while(milestones.i > length(milestones)) {
              cat("#")
            }
            if (.Platform$OS.type == "windows")
            flush.console()
          })

## to avoid 'loosing' the default update.
## (not sure this is the most elegant way to do this)


setMethod("update", "ProgressBarText",
          function(object) {
            increment <- get("increment", object@internals)
            i <- get("i", object@internals) + increment
            milestones.i <- get("milestones.i", object@internals)
            milestones <- get("milestones", object@internals)
            touched <- FALSE
            while(milestones.i <= length(milestones) && i >= milestones[milestones.i]) {
              cat("#")
              milestones.i <- milestones.i + increment
              touched <- TRUE
            }
            ## the 'touch' thing appears to make it save 0.1 sec / 100000 iteration
            ## (which makes it absolutely mandatory :) ).
            if (touched) {
              assign("milestones.i", milestones.i, envir = object@internals)
              if (.Platform$OS.type == "windows")
                flush.console()
            }
            assign("i", i, , envir = object@internals)
          })


setMethod("close", "ProgressBarText",
          function(con) {
            increment <- get("increment", con@internals)
            milestones.i <- get("milestones.i", con@internals)
            milestones <- get("milestones", con@internals)
            while(milestones.i <= length(milestones)) {
              cat("#")
              milestones.i <- milestones.i + increment
            }
            assign("milestones.i", milestones.i, envir = con@internals)
            cat("|\n")
            if (.Platform$OS.type == "windows")
              flush.console()
          })
