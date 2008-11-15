barplot.ProbeSet <- function(height,
                             xlab="Probe pair",ylab="Intensity",
                             main=NA,
                             col.pm="red", col.mm="blue",
                             beside=TRUE, names.arg="pp",
                             ask = TRUE, scale = TRUE,
                             ...)
{

  opar <- par()$ask
  par(ask=ask)
  on.exit(par(ask=opar))

  if (names.arg == "pp") {
    names.arg <- seq(1, nrow(pm(height)))
  }

  col <- c(col.pm, col.mm)

  if (scale) {
    ylim <- range(c(pm(height), mm(height)), na.rm=TRUE)
  } else {
    ylim <- NULL
  }

  if (is.na(main)) {
    main <- paste(height@id, "( sample", 1:ncol(pm(height)), ")")
  } else {
    main <- rep(main, length=ncol(pm(height)))
  }
  
  for (i in 1:ncol(pm(height))) {
    
    hh <- rbind(pm(height)[, i], mm(height)[, i])
      
    barplot(hh, xlab=xlab, ylab=ylab,
            main=main[i],
            col=col,
            beside=beside,
            names.arg=names.arg,
            ylim = ylim,
            ...)
  }
}
