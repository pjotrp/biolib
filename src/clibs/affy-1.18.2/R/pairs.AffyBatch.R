pairs.AffyBatch <- function(x, panel=points, ..., transfo=I, main=NULL, oma=NULL,
                            font.main = par("font.main"), cex.main = par("cex.main"),
                            cex.labels = NULL, 
                            lower.panel=panel, upper.panel=NULL,
                            diag.panel=NULL,
                                        #text.panel = textPanel,
                                        #label.pos = 0.5 + has.diag/3,                                
                            font.labels = 1, row1attop = TRUE, gap = 1) {

  #label1 <- chipNames(x)
  #label2 <- unlist(lapply(history(x), function(z) z$name))
  
  #textPanel <- function(x = 0.5, y = 0.5, txt, cex, font) {
  #  text(x, y, txt, cex = cex, font = font)
  #}
  
  ##labels <- paste(sampleNames(x), unlist(lapply(history(x), function(z) if (is.null(z$name)) "" else z$name)), sep="\n")
  labels <- sampleNames(x)
  ##y <- matrix(intensity(x)[, , seq(along=x)], ncol=length(x))
  y <- intensity(x)
  
  pairs(transfo(y), labels=labels,
        panel=panel, ..., main=main, oma=oma,
        font.main = font.main, cex.main = cex.main,
        lower.panel=lower.panel, upper.panel=upper.panel, diag.panel=diag.panel,
        #text.panel = text.panel,
        #label.pos = label.pos,
        cex.labels = cex.labels, 
        font.labels = font.labels, row1attop = row1attop, gap = gap
        )
   
}
