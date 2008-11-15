merge.AffyBatch <- function(x, y, annotation=paste(annotation(x), annotation(y)),
                            description=NULL,
                            notes=character(0), ...) {

  adim <- dim(intensity(x))[1]

  if ((nrow(x) != nrow(y)) || (ncol(x) != ncol(y)))
    stop("cannot merge chips of different sizes !")

  if (cdfName(x) != cdfName(y))
    warning("cdfName mismatch (using the cdfName of x)!")

  if (is.null(description)){
    description <- new("MIAME")
    description@title <- "Created from merging two AffyBatches. No description was supplied. The description of the two original AffyBatches was not kept."
  }                       

  lx <- length(x)
  ly <- length(y)

  phenodata <- phenoData(x)
  pData(phenodata) <- rbind(pData(x),pData(y))
  notes(description) <- 
    if (length(notes)==0) 
      list(paste("Merge from two AffyBatches with notes: 1)", notes(experimentData(x)), ", and 2)",notes(experimentData(y))))
    else notes
  return(new("AffyBatch",
             exprs=cbind(intensity(x),intensity(y)),
             phenoData=phenodata,
             experimentData=description, ##need to write a merge for MIAME
             cdfName=cdfName(x),
             nrow=nrow(x),
             ncol=ncol(x),
             annotation=x@annotation
         ))
}
