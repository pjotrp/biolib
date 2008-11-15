rcModelPLMr <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")
  PsiCode <- 0
  PsiK <- 1.345
  .Call("R_plmr_model",y,PsiCode,PsiK,PACKAGE="preprocessCore")
}

rcModelPLMrr <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")
  PsiCode <- 0
  PsiK <- 1.345
  .Call("R_plmrr_model",y,PsiCode,PsiK,PACKAGE="preprocessCore")
}


rcModelPLMrc <- function(y){
  if (!is.matrix(y))
    stop("argument should be matrix")
  PsiCode <- 0
  PsiK <- 1.345
  .Call("R_plmrc_model",y,PsiCode,PsiK,PACKAGE="preprocessCore")
}





rcModelWPLMr <- function(y, w){
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
    stop("weights should be non negative")
  }

  
    
  PsiCode <- 0
  PsiK <- 1.345
  .Call("R_wplmr_model",y,PsiCode,PsiK,as.double(w),PACKAGE="preprocessCore")

}


rcModelWPLMrr <- function(y, w){
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
    stop("weights should be non negative")
  }

  
    
  PsiCode <- 0
  PsiK <- 1.345
  .Call("R_wplmrr_model",y,PsiCode,PsiK,as.double(w),PACKAGE="preprocessCore")

}


rcModelWPLMrc <- function(y, w){
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
    stop("weights should be non negative")
  }

  
    
  PsiCode <- 0
  PsiK <- 1.345
  .Call("R_wplmrc_model",y,PsiCode,PsiK,as.double(w),PACKAGE="preprocessCore")

}

