rcModelPLMd <- function(y,group.labels){
  if (!is.matrix(y))
    stop("argument should be matrix")

  if (length(group.labels) != ncol(y)){
    stop("group labels is of incorrect length")
  }  

  if (!is.factor(group.labels)){
    group.labels <- as.factor(group.labels)
  }
  
  if (any(table(group.labels) < 2)){
     stop("Must be at least two arrays in each group")
  }

  
  group.int <- as.integer(group.labels) -1
	
  PsiCode <- 0
  PsiK <- 1.345


  .Call("R_plmd_model",y,PsiCode,PsiK,as.integer(group.int),as.integer(length(unique(group.labels))),PACKAGE="preprocessCore")
							 
}


