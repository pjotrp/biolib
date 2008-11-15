bg.correct.mas <- function(object, griddim=16)
{
   nchips <- length(object)

   pm.index <- unique(unlist(indexProbes(object, "pm")))
   mm.index <- unique(unlist(indexProbes(object, "mm")))

   rows <- nrow(object)
   cols <- ncol(object)

   allintensities <- intensity(object)[c(pm.index, mm.index), ]

   # note that the indexing is +1 more than you'd expect because
   # the c code expects it that way
   ## (note about the remark above: R indexing starts at 1 and not at 0,
   ## that's why the indexing is done this way. The package is primarily done to
   ## be used with R...)

   allx <- c(pm.index-1, mm.index-1) %% nrow(object) +1
   ally <- c(pm.index-1, mm.index-1) %/% nrow(object) + 1

   nprobes <- length(allx)

   corrected <- matrix(.C("affy_background_adjust_R",
                          as.double(as.vector(allintensities)), as.integer(allx), as.integer(ally),
                          as.integer(nprobes), as.integer(nchips), as.integer(rows), as.integer(cols),
                          as.integer(griddim), PACKAGE="affy")[[1]],
                       nprobes, nchips)

   intensity(object)[c(pm.index, mm.index), ] <- corrected
   ## and what with the 'non pm or mm' probes ?
   ## answer: they are not used per Affymetrix Statistical Algorithms Description Document.

   return(object)

 }
