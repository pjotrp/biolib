   
hlog <- function(x,constant=1){ #constant is where the change occurs
  if(constant<=0){
    warning("constant less than or equal to 0. Returning log(x)\n")
    return(log(x))
  }
  else{
    if(constant==Inf)
      return(x)
    else{
      aux <- (abs(x)<constant)*(x) +
        (abs(x)>=constant)*(sign(x)*(constant*log(abs(x/constant))+constant))
      aux[x==0] <- 0
      return(aux)
    }
  }
}
