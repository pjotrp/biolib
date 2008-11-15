getCdfInfo <- function(object,  how=getOption("BioC")$affy$probesloc, verbose=FALSE) {
    ## cdfname is the cdf environment
    ## methods is a vector detailing how to get the file - one of
    ## 'environment', 'data', 'library', 'bioC'
    ## where is used for specific information corresponding to method

    if (length(how) == 0)
        stop("No available method to obtain CDF file")

    cdfname <- cdfName(object)

    badOut <- list()
    for (i in 1:length(how)) {
        cur <- how[[i]]
        out <- switch(cur$what,
                      "environment" = cdfFromEnvironment(cdfname,
                      cur$where, verbose),
                      "data" = cdfFromData(cdfname, cur$where, verbose),
                      "libPath" = cdfFromLibPath(cdfname, cur$where,
                      verbose=verbose),
                      "bioC" = cdfFromBioC(cdfname, cur$where,
                      verbose)
                      )

        if (is.environment(out))
            return(out)
        else
            badOut <- c(badOut, out)
    }

    stop(paste("Could not obtain CDF environment, problems encountered:",
               paste(unlist(badOut),collapse="\n"),sep="\n"))
}

cdfFromData <- function(cdfname, pkg, verbose=TRUE) {
    cdfname <- cleancdfname(cdfname)
    if (verbose)
        print(paste("Attempting to locate",cdfname,
                    "in the data directory of package", pkg))

    if(cdfname %in% do.call("data", list(package=pkg))$results[, 3]) {
        where.env <- pos.to.env(match(paste("package:", pkg, sep = ""), search()))

        ## check if the cdfenv is already loaded. If not load it *in* the environment
        ## of the package (where.env)
        if(!exists(cdfname, where = where.env, inherits = FALSE)) {
            path <- system.file(package=pkg)
            data(list=cdfname, envir=where.env)
        }
        cdfenv <- get(cdfname, envir=where.env)
        return(cdfenv)
    }
    else
        return(list(paste("Data for package",pkg,"did not contain",cdfname)))
}

cdfFromEnvironment <- function(cdfname, where, verbose=TRUE) {
    if (verbose)
        print(paste("Attempting to locate",cdfname,"in specified environment"))

    if (exists(cdfname, inherits=FALSE, where=where))
        return(as.environment(get(cdfname,inherits=FALSE,envir=where)))
    else {
        if (verbose)
            print(paste("Specified environment does not contain",cdfname))
        return(list(paste("Specified environment does not contain",cdfname)))
    }
}

cdfFromBioC <- function(cdfname, lib=.libPaths()[1], verbose=TRUE) {
    cdfname <- cleancdfname(cdfname)
    if (verbose)
      print(paste("Attempting to obtain",cdfname,"from Bioconductor website"))

    ## First try libPaths
    libs <- .libPaths()
    if (!all(lib %in% libs))
      libs <- unique(c(lib, libs))
    result <- cdfFromLibPath(cdfname, lib=libs, verbose=verbose)
    if (is.environment(result))
      return(result)

    if (length(lib) > 1) {
        warning("Ignoring all but first element of argument lib")
        lib <- lib[1]
    }

    if (verbose)
      print(paste("The environment ",cdfname," was not found in",
                  " these directories: ",
                  paste(libs, collapse=", "),
                  ".  Now searching the internet repository.",
                  sep=""))
    if (verbose)
      print(paste("Checking to see if your internet connection works ..."))
    if (testBioCConnection()) {
        ## Check for file permissions
        if (file.access(lib, mode=0) < 0) {
            if (verbose) {
                print(paste("Directory",lib,"does not seem to exist.\n",
                            "Please check your 'lib' parameter and try again"))
                return(list("Bioconductor - lib does not exist"))
            }
        }
        
        if (file.access(lib,mode=2) < 0) {
            if (verbose) {
                print(paste("You do not have write access to",lib,
                            "\nPlease check your permissions or provide",
                            "a different 'lib' parameter"))
                return(list("Bioconductor - lib is not writeable"))
            }
        }

        biocContribUrl <- sapply(Biobase:::biocReposList(), contrib.url)
        biocPkgs <- available.packages(biocContribUrl)
        if (! cdfname %in% biocPkgs[, "Package"]) {
            if (verbose)
              print(paste("Environment",cdfname,
                          "was not found in the Bioconductor",
                          "repository."))
            return(list(paste("Bioconductor -",cdfname,"not available")))
        } else {
            install.packages(cdfname, lib=lib,
                             repos=Biobase:::biocReposList(),
                             dependencies=TRUE)
            ## no way to know if we succeeded or not, with install.packages
            ##if (verbose)
            ##  print(paste("Installation of environment",
            ##              cdfname, "was succesful."))
        }
    } else {
        if (verbose)
          print(paste("The current operation could not access",
                      "the Bioconductor repository.  Please",
                      "check your internet connection, and",
                      "report further problems to",
                      "bioconductor@stat.math.ethz.ch"))
        return(list("Bioconductor - could not connect"))
    }
    return(cdfFromLibPath(cdfname, lib=lib, verbose=verbose))
}

cdfFromLibPath <- function(cdfname, lib = NULL, verbose=TRUE) {
    cdfname <- cleancdfname(cdfname)
    ## First check to see if package is installed
    if (verbose)
      print(paste("Checking to see if package",cdfname,
                  "is already installed"))

    if (length(.find.package(cdfname, lib.loc=lib, quiet=TRUE)) == 0)
      return(list(paste("Library - package",cdfname,"not installed")))

    ## See if package is already loaded
    if (cdfname %in% .packages()) {
        if (verbose)
          print(paste("The package", cdfname, "is already loaded"))
    }
    else {
        if (verbose)
          print(paste("Attempting to load package", cdfname))
        ## Attempt to load the library requested
        do.call("library", list(cdfname, lib.loc=lib, character.only=TRUE))

        ## Check to see if it got loaded
        if (! cdfname %in% .packages()) {
            ## package didn't get loaded
            if (verbose)
              print(paste("The package", cdfname, "could not be loaded"))
            return(list(paste("Library - package",cdfname,"is not loadable")))
        }
    }

    return(get(cdfname, envir=as.environment(paste("package:", cdfname, sep=""))))
}
