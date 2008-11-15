"AffyRNAdeg" <-
function (abatch,log.it=TRUE)
{
    {
        data <- pm(abatch, LIST = TRUE)
        if(log.it==TRUE) data <- lapply(data,log2)
        names <- colnames(exprs(abatch))
        probe.set.size <- function(x) {
            size <- dim(x)[1]
            return(size)
        }
        max.num <- sapply(data, probe.set.size)
        tab <- (table(max.num))
        ord <- order(-as.numeric(tab))
        K <- as.numeric(names(tab))[ord[1]]
        data <- data[max.num == K]
    }
    get.row <- function(x, i = 1) {
        return(x[i, ])
    }
    get.col <- function(x, i = 1) {
        return(x[, i])
    }
    rowstack <- function(x, i = 1) {
        return(t(sapply(x, get.row, i)))
    }
    colstack <- function(x, i = 1) {
        return(t(sapply(x, get.col, i)))
    }
    N <- length(data)

    n <- dim(data[[1]])[2]
    mns <- matrix(nrow = n, ncol = K)
    sds <- mns
    for (i in 1:K) {
        data.stack <- rowstack(data, i)
        if(dim(data[[1]])[2]==1) data.stack <- t(data.stack)
        mns[, i] <- colMeans(data.stack)
        sds[, i] <- apply(data.stack, 2, sd)
    }
    mns.orig <- mns
    mn <- mns[, 1]
    mns <- sweep(mns, 1, mn)
    mns <- mns/(sds/sqrt(N))
    lm.stats <- function(x) {
        index <- 0:(length(x) - 1)
        ans <- summary(lm(x ~ index))$coefficients[2, c(1, 4)]
        return(ans)
    }
    stats <- apply(mns, 1, lm.stats)
    answer <- list(N, names, mns.orig, sds/sqrt(N), stats[1,
        ], stats[2, ])
    names(answer) <- c("N", "sample.names", "means.by.number",
        "ses", "slope", "pvalue")
    return(answer)
}
"summaryAffyRNAdeg" <-
function (rna.deg.obj, signif.digits = 3)
{
  temp.table <- rbind(signif(rna.deg.obj$slope, signif.digits),
                      signif(rna.deg.obj$pvalue, signif.digits))
  colnames(temp.table) <- rna.deg.obj$sample.names
  rownames(temp.table) <- c("slope", "pvalue")
  ##write.table(temp.table, file = "", quote = FALSE)
  return(temp.table)
}
"plotAffyRNAdeg" <-
function (rna.deg.obj,transform="shift.scale",cols=NULL, ...)
{
    if(!is.element(transform,c("shift.scale","shift.only","neither"))) stop("Tranform must be 'shift.scale','shift.only', or 'neither'")
    mns <- rna.deg.obj$means.by.number
    if(is.null(cols)) cols=rep(4,dim(mns)[1])
    ylab="Mean Intensity"
    if(transform=="shift.scale"){
    sds <- rna.deg.obj$ses
    mn <- mns[, 1]
    mns <- sweep(mns, 1, mn)
    mns <- mns/(sds)
    mns <- sweep(mns, 1, 1:(dim(mns)[1]), "+")
    ylab <- paste(ylab,": shifted and scaled")
   }else if(transform=="shift.only"){
    mn <- mns[, 1]
    mns <- sweep(mns, 1, mn)
    mns <- sweep(mns, 1, 1:(dim(mns)[1]), "+")
    ylab <- paste(ylab,": shifted")
   }
    plot(-2, -1, pch = "", xlim = range(-1, (dim(mns)[2])),
        ylim = range(min(as.vector(mns)) - 1, max(as.vector(mns)) + 1), xlab = "5' <-----> 3'\n Probe Number ",
        ylab = ylab, axes = FALSE, main = "RNA degradation plot",
        ...)
    axis(1)
    axis(2)
    for (i in 1:dim(mns)[1]) lines(0:((dim(mns)[2]-1)), mns[i, ],col=cols[i])
}




