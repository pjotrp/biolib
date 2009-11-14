# A function that takes user inputs for correction methods for
# expresso (affy). Default values can be missing, in which case the
# first element will be chosen as the default.

expressoWidget <- function(BGMethods, normMethods, PMMethods, expMethods,
                           BGDefault, normDefault, PMDefault, expDefault){
    methodList <- list()
    END <- FALSE

    if(any(missing(BGMethods), missing(normMethods),
           missing(PMMethods), missing(expMethods))){
        stop("At least one of the method arguments is missing")
    }
    if(any(c(length(BGMethods), length(normMethods),
             length(PMMethods), length(expMethods)) == 0)){
        stop("At least one of the method argument is of length 1")
    }

    if(missing(BGDefault)){
        BGM <- tclVar(BGMethods[1])
    }else{
        BGM <- tclVar(BGDefault)
    }
    if(missing(normDefault)){
        NMM <- tclVar(normMethods[1])
    }else{
        NMM <- tclVar(normDefault)
    }
    if(missing(PMDefault)){
        PMM <- tclVar(PMMethods[1])
    }else{
        PMM <- tclVar(PMDefault)
    }
    if(missing(expDefault)){
        EXM <- tclVar(expMethods[1])
    }else{
        EXM <- tclVar(expDefault)
    }


    quit <- function(){
        tkdestroy(base)
    }
    end <- function(){
        END <<- TRUE
        methodList[["BG"]] <<- tclvalue(BGM)
        methodList[["NORM"]] <<- tclvalue(NMM)
        methodList[["PM"]] <<- tclvalue(PMM)
        methodList[["EXP"]] <<- tclvalue(EXM)
        quit()
    }

    base <- tktoplevel()
    ## post -- hook
    on.exit(tkdestroy(base))

    tktitle(base) <- "Expresso methods selection"
    ## Description text
    tkpack(tklabel(base, text = "Welcome to Expresso methods selection"),
           expand = FALSE, fill = "x", padx = 5, pady = 5)
    tkpack(tklabel(base, text = paste("You need to choose correction",
                         "methods or go with the defaults")),
           expand = FALSE, fill = "x", padx = 5)

    ## Selections for correction methods
    methodFrame <- tkframe(base)
    ## Background selection
    BGLabel <- tklabel(methodFrame, text = "Background correction")
    BGDropdown <- tkframe(methodFrame)
    dropdownList(BGDropdown, BGMethods, BGM, 20,
                                      tclvalue(BGM), TRUE)
    tkgrid(BGLabel, BGDropdown)
    tkgrid.configure(BGLabel, sticky = "e")
    tkgrid.configure(BGDropdown, sticky = "w")

    ## Normlization
    NMLabel <- tklabel(methodFrame, text = "Normalization")
    NMDropdown <- tkframe(methodFrame)
    dropdownList(NMDropdown,normMethods, NMM, 20,
                                      tclvalue(NMM), TRUE)
    tkgrid(NMLabel, NMDropdown)
    tkgrid.configure(NMLabel, sticky = "e")
    tkgrid.configure(NMDropdown, sticky = "w")

    ## PM correction
    PMLabel <- tklabel(methodFrame, text = "PM correction")
    PMDropdown <- tkframe(methodFrame)
    dropdownList(PMDropdown, PMMethods, PMM, 20,
                                      tclvalue(PMM), TRUE)
    tkgrid(PMLabel, PMDropdown)
    tkgrid.configure(PMLabel, sticky = "e")
    tkgrid.configure(PMDropdown, sticky = "w")

    ## PM correction
    EXLabel <- tklabel(methodFrame, text = "Expression")
    EXDropdown <- tkframe(methodFrame)
    dropdownList(EXDropdown, expMethods, EXM, 20,
                                      tclvalue(EXM), TRUE)
    tkgrid(EXLabel, EXDropdown)
    tkgrid.configure(EXLabel, sticky = "e")
    tkgrid.configure(EXDropdown, sticky = "w")

    tkpack(methodFrame, expand = TRUE, fill = "both", padx = 5,
           pady = 10)

    butFrame <- tkframe(base)
    quitBut <- tkbutton(butFrame, text = "Quit", width = 7, command = quit)
    endBut <- tkbutton(butFrame, text = "Select", width = 7, command = end)
    tkgrid(quitBut, endBut, padx = 5)
    tkpack(butFrame, expand = FALSE, fill = "x", pady = 5)

    tkwait.window(base)

    if(END){
        return(methodList)
    }else{
        return(NULL)
    }
}
