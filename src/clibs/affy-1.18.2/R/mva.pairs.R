###
###
### Code for M and MvA plots
###
### Mar 6, 2004 - added the generic Mbox. It performs
###               the equivalent of Mbox in affyPLM
###               added a generic MAplot. Similar
###               functionality is implemented in
###               affyPLM
###               a function ma.plot now does the actual plotting
###               for mva.pairs
###
### Aug 23, 2004 - change the placement location of statistics in
###                ma.plot
### Nov 30, 2005 - fix double logging when pairs=TRUE in MAplot
### Feb 15, 2006 - fixed passing of cex variable into mva.pairs
### Feb 24, 2006 - add smoothScatter option to ma.plot
### Apr 11, 2006 - fix problem with smoothScatter option.
### Jun 22, 2006 - Fix problem with where statistics appear when xlim is set. Add plotmethod="add". move pch to MAplot. Fix it so cex is passed down to plot(). Make adding the loess line optional. Make lwd,lty,col settable for the loess line
### Jul 21, 2006 - allow MAplot to have character string sampleName arguments for which,subset,ref. But then removed subset
### Jul 23, 2006 - added groups to MAplot for AffyBatch
### Aug  4, 2006 - fix small bug in how plots are titled.
### Oct 11, 2006 - change some apply(x,1,median) to rowMedians(x)
###

ma.plot <- function(A,M,subset=sample(1:length(M),min(c(10000, length(M)))),show.statistics=TRUE,span=2/3,family.loess="gaussian",cex=2,plot.method=c("normal","smoothScatter","add"),add.loess=TRUE,lwd=1,lty=1,loess.col="red",...){

  plot.method <- match.arg(plot.method)
  
  fn.call <- list(...)

  sigma <- IQR(M)
  mean <- median(M)
  if (!is.element("ylim",names(fn.call))){
    yloc <- max(M)
  } else {
    yloc <- max(fn.call$ylim)
  }
  if (!is.element("xlim",names(fn.call))){
    xloc <- max(A)
  } else {
    xloc <- max(fn.call$xlim)
  }
  
  if(plot.method == "smoothScatter"){
    require("geneplotter")
    plotmethod <- "smoothScatter"
  } else if (plot.method == "add"){
    plotmethod <- "add"
  } else {
    plotmethod <- "normal"
  }
  
  

  
  aux <- loess(M[subset]~A[subset],degree=1,span=span,family=family.loess)$fitted
  if (plotmethod == "smoothScatter"){
    smoothScatter(A,M,...)
  } else if (plotmethod == "add"){
    points(A,M,cex=cex,...)
  } else {
    plot(A,M,cex=cex,...)
  }

  if (add.loess){
    o <- order(A[subset])
    A <- A[subset][o]
    M <- aux[o]
    o <-which(!duplicated(A))
    lines(approx(A[o],M[o]),col=loess.col,lwd=lwd,lty=lty)
  }
  abline(0,0,col="blue")
  

    
  # write IQR and Median on to plot
  if (show.statistics){
    txt <- format(sigma,digits=3)
    txt2 <- format(mean,digits=3)
    text(xloc ,yloc,paste(paste("Median:",txt2),paste("IQR:",txt),sep="\n"),cex=cex,adj=c(1,1))
  }

  
}



mva.pairs <- function(x,labels=colnames(x),log.it=TRUE,span=2/3,family.loess="gaussian",
                      digits=3,line.col=2,main="MVA plot", cex = 2, ...){
  if(log.it) x <-log2(x)
  J <- dim(x)[2]
  frame()
  old.par <- par(no.readonly = TRUE)
  on.exit(par(old.par))
  par(mfrow=c(J,J),mgp=c(0,.2,0),mar=c(1,1,1,1),oma=c(1,1.4,2,1))
  for(j in 1:(J-1)){
    par(mfg=c(j,j))
    plot(1,1,type="n",xaxt="n",yaxt="n",xlab="",ylab="")
    text(1,1,labels[j],cex=cex)
    for(k in (j+1):J){
      par(mfg=c(j,k))
      yy <- x[,j]-x[,k]
      xx <-(x[,j]+x[,k])/2
      sigma <- IQR(yy)
      mean <- median(yy)
      ma.plot(xx,yy,tck=0,show.statistics=FALSE,pch=".",xlab="",ylab="",tck=0,span=span,...)
      par(mfg=c(k,j))
      #sigma <- IQR(yy)
      txt <- format(sigma,digits=digits)
      txt2 <- format(mean,digits=digits)
      plot(c(0,1),c(0,1),type="n",ylab="",xlab="",xaxt="n",yaxt="n")
      text(0.5,0.5,paste(paste("Median:",txt2),paste("IQR:",txt),sep="\n"),cex=cex)
    }
  }
  par(mfg=c(J,J));plot(1,1,type="n",xaxt="n",yaxt="n",xlab="",ylab="");
  text(1,1,labels[J],cex=cex)
  mtext("A",1,outer=TRUE,cex=1.5)
  mtext("M",2,outer=TRUE,cex=1.5,las=1)
  mtext(main,3,outer=TRUE,cex=1.5)
  invisible()
}









setGeneric("Mbox",function(object,...)
           standardGeneric("Mbox"))


setMethod("Mbox",signature("AffyBatch"),
          function(object,log=TRUE,type=c("both","pm","mm"),...){
             type <- match.arg(type)
             if (type == "both"){
              pms <- unlist(indexProbes(object, "both"))
            } else if (type == "pm"){
              pms <- unlist(pmindex(object))
            } else if (type == "mm"){
              mms <- unlist(mmindex(object))
            }
            if(log){
              x <- log2(intensity(object)[pms, ])
            } else {
              x <- intensity(object)[pms, ]
            }
            medianchip <- rowMedians(x)
            M <- sweep(x,1,medianchip,FUN='-')
            boxplot(data.frame(M),...)
          })

setGeneric("MAplot",function(object,...)
           standardGeneric("MAplot"))


setMethod("MAplot",signature("AffyBatch"),
          function(object,log=TRUE,type=c("both","pm","mm"),groups=NULL,ref=NULL,which=NULL,pairs=FALSE,pch=".",ref.fn=c("median","mean"),ref.title="vs pseudo-median reference chip",...){

            type <- match.arg(type)
            if (type == "both"){
              pms <- unlist(indexProbes(object, "both"))
            } else if (type == "pm"){
              pms <- unlist(pmindex(object))
            } else if (type == "mm"){
              pms <- unlist(mmindex(object))
            }
            if(log){
              x <- log2(intensity(object)[pms, ])
            } else {
              x <- intensity(object)[pms, ]
            }
            
            if (is.null(groups)){
              if (is.character(ref)){
                ref.indices <- match(ref,sampleNames(object))
                if (all(is.na(ref.indices))){
                  stop("No known sampleNames in ref")
                }
                
                if (any(is.na(ref.indices))){
                  warning(paste("Omitting the following from ref:",ref[is.na(ref.indices)], "because they can not be found."))
                }
                ref <- ref.indices[!is.na(ref.indices)]
              }
            
              if (is.character(subset)){
                subset.indices <- match(subset,sampleNames(object))
                if (all(is.na(subset.indices))){
                  stop("No known sampleNames in subset")
                }
                
                if (any(is.na(subset.indices))){
                  warning(paste("Omitting the following from subset:",subset[is.na(subset.indices)], "because they can not be found."))
                }
                subset <- subset.indices[!is.na(subset.indices)]
              }
              
              if (is.character(which)){
                which.indices <- match(which,sampleNames(object))
                if (all(is.na(which.indices))){
                  stop("No known sampleNames in which")
                }
                
                if (any(is.na(which.indices))){
                  warning(paste("Omitting the following from which:",which[is.na(which.indices)], "because they can not be found."))
                }
                which <- which.indices[!is.na(which.indices)]
              }
              
              
              if (is.null(which)){
                which <- 1:dim(exprs(object))[2]
              }
              
              ref.fn <- match.arg(ref.fn)

              if(!pairs){
                if (is.null(ref)){
                  medianchip <- rowMedians(x)            ###apply(x, 1, median)
                }  else if (length(ref) > 1){
                  if (ref.fn == "median"){
                    medianchip <- rowMedians(x[,ref])
                  } else {
                    medianchip <- rowMeans(x[,ref])
                  }
                } else {
                  medianchip <- x[,ref]
                }
                
                M <- sweep(x,1,medianchip,FUN='-')
                A <- 1/2*sweep(x,1,medianchip,FUN='+')
                if (is.null(ref)){
                  for (i in which){
                    title <- paste(sampleNames(object)[i],"vs pseudo-median reference chip")
                    ma.plot(A[,i],M[,i],main=title,xlab="A",ylab="M",pch=pch,...)
                  }
                } else {
                  for (i in which){
                    if (i != ref){ ##changed which to i
                      title <- paste(sampleNames(object)[i],"vs",sampleNames(object)[ref])
                      ma.plot(A[,i],M[,i],main=title,xlab="A",ylab="M",pch=pch,...)
                    }
                  }
                }
                
              } else {
                if(!is.null(ref)) stop("Can't use pairs with non-null 'ref'")
                if(is.null(which)) which <- 1:ncol(x)
                mva.pairs(x[,which],log.it=FALSE,...)
              }
            } else {
              ## group labels have been given
              ## check that group variable is of same length as number of samples 
                
              if (dim(x)[2] != length(groups)){
                stop("'groups' is of wrong length.")
              }
              
              
              ### group labels variable can be integer, character or factor variable.
              ### need to check that if any names supplied
              ### for ref or which can be found in group.labels
                
              if (!is.null(which)){
                if (is.numeric(groups)){
                  if (!is.numeric(which)){
                    stop("'which' labels must also be found in 'groups'") 
                  } else {
                    if (!all(is.element(which,groups))){
                      stop("'which' labels must also be found in 'groups'") 
                    }
                  }
                } else if (is.factor(groups)){
                  if (!is.character(which)){
                    stop("'which' should be character vector") 
                  } else {
                    if (!all(is.element(which,as.character(groups)))){
                      stop("'which' labels must also be found in 'groups'") 
                    }
                  }
                } else if (is.character(groups)){
                  if (!is.character(which)){
                    stop("'which' should be character vector") 
                  } else {
                    if (!all(is.element(which,groups))){
                      stop("'which' labels must also be found in 'groups'") 
                    }
                  }
                }
              }
              
              if (!is.null(ref)){
                if (is.numeric(groups)){
                  if (!is.numeric(ref)){
                    stop("'ref' labels must also be found in 'groups'") 
                  } else {
                    if (!all(is.element(ref,groups))){
                      stop("'ref' labels must also be found in 'groups'") 
                    }
                  }
                } else if (is.factor(groups)){
                  if (!is.character(ref)){
                    stop("'ref' should be character vector") 
                  } else {
                    if (!all(is.element(ref,as.character(groups)))){
                      stop("'ref' labels must also be found in 'groups'") 
                    }
                  }
                } else if (is.character(groups)){
                  if (!is.character(ref)){
                    stop("'ref' should be character vector") 
                  } else {
                    if (!all(is.element(ref,groups))){
                      stop("'ref' labels must also be found in 'groups'") 
                    }
                  }
                }
              }
              
              ref.fn <- match.arg(ref.fn)
              
              groups.list <- split(1:dim(x)[2], as.factor(groups))
              
              
              grouped.data <- matrix(0,nrow(x),length(groups.list))
              colnames(grouped.data) <- names(groups.list)
              which.col <- 1
              for (group in groups.list){
                grouped.data[,which.col] <- rowMeans(x[,group,drop=FALSE])
                which.col <- which.col + 1
              }
              
              
              if (!pairs){
                if (is.null(which)){
                  which <- names(groups.list)
                }
                
                if (is.null(ref)){
                  if (ref.fn == "median"){
                    medianchip <- rowMedians(grouped.data)    ####apply(grouped.data, 1, median)
                  } else {
                    medianchip <- rowMeans(grouped.data)
                  }
                  
                } else if (length(ref) == 1){
                  ref.name <- ref
                  ref <- match(ref,names(groups.list))
                  medianchip <- grouped.data[,ref]
                } else {
                  ref <- match(ref,names(groups.list))
                  if (ref.fn == "median"){
                    medianchip <- rowMedians(grouped.data[,ref])
                  } else {
                    medianchip <- rowMeans(grouped.data[,ref])
                  }
                  
                }
                
                M <- sweep(grouped.data,1,medianchip,FUN='-')
                A <- 1/2*sweep(grouped.data,1,medianchip,FUN='+')
                if (is.null(ref)){
                  for (i in which){
                    title <- paste(i,ref.title)
                    ma.plot(A[,i],M[,i],main=title,xlab="A",ylab="M",pch=pch,...)
                  }
                } else {
                  for (i in which){
                    if (length(ref) == 1){
                      if (i != ref.name){
                        title <- paste(i,"vs",ref.name)
                        ma.plot(A[,i],M[,i],main=title,xlab="A",ylab="M",pch=pch,...)
                      }
                    } else {
                      title <- paste(i,ref.title)
                      ma.plot(A[,i],M[,i],main=title,xlab="A",ylab="M",pch=pch,...)
                    }
                  }
                }
              } else {
                if (!is.null(ref)) stop("Can't use pairs with non-null 'ref'")
                if (is.null(which)){
                  which <- names(groups.list)
                }
                
                mva.pairs(grouped.data[,which],log.it=FALSE,...)
              }
            }
          })
