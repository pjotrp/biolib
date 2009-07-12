


rcModelPLM <- function(y,row.effects=NULL){
  if (!is.matrix(y))
    stop("argument should be matrix")
  PsiCode <- 0
  PsiK <- 1.345
  if (is.null(row.effects)){
    .Call("R_rlm_rma_default_model",y,PsiCode,PsiK,PACKAGE="preprocessCore")
  } else {
    if (length(row.effects) != nrow(y)){
       stop("row.effects parameter should be same length as number of rows")
    }  
    if (abs(sum(row.effects)) > 10*.Machine$double.eps){
       stop("row.effects should sum to zero")
    }
    .Call("R_rlm_rma_given_probe_effects",y,as.double(row.effects),PsiCode,PsiK,PACKAGE="preprocessCore") 
  }	
}



rcModelWPLM <- function(y, w, row.effects=NULL){
  if (!is.matrix(y))
    stop("argument should be matrix")
  if (is.vector(w)){
    if (length(w) != prod(dim(y))){
      stop("weights are not correct length")
    }
  } else if (is.matrix(w)){
    if (!all(dim(w) == dim(y))){
      stop("weights should be same dimension as input matrix")
    }

  }
  if (any(w < 0)){
    stop("weights should be no negative")
  }

  
    
  PsiCode <- 0
  PsiK <- 1.345 
  if (is.null(row.effects)){
     .Call("R_wrlm_rma_default_model",y,PsiCode,PsiK,as.double(w),PACKAGE="preprocessCore")
  } else {
    if (length(row.effects) != nrow(y)){
       stop("row.effects parameter should be same length as number of rows")
    }  
    if (abs(sum(row.effects)) > 10*.Machine$double.eps){
       stop("row.effects should sum to zero")
    }
    .Call("R_wrlm_rma_given_probe_effects",y,as.double(row.effects),PsiCode,PsiK,as.double(w),PACKAGE="preprocessCore") 
  }	

}



rcModelMedianPolish <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")
  PsiCode <- 0
  PsiK <- 1.345
  .Call("R_medianpolish_rma_default_model",y,PACKAGE="preprocessCore")
}
