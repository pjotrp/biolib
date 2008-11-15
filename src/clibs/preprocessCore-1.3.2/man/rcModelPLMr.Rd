\name{rcModelPLMr}
\alias{rcModelPLMr}
\alias{rcModelPLMrr}
\alias{rcModelPLMrc}
\alias{rcModelWPLMr}
\alias{rcModelWPLMrr}
\alias{rcModelWPLMrc}

\title{Fit robust row-column models to a matrix}
\description{These functions fit row-column effect models to matrices using PLM-r and variants
}
\usage{
rcModelPLMr(y)
rcModelPLMrr(y)
rcModelPLMrc(y)
rcModelWPLMr(y, w)
rcModelWPLMrr(y, w)
rcModelWPLMrc(y, w)

}
\arguments{
  \item{y}{A numeric matrix}
  \item{w}{A matrix or vector of weights. These should be non-negative.}
}
\value{
  A list with following items:
  \item{Estimates}{The parameter estimates. Stored in column effect then
    row effect order}
  \item{Weights}{The final weights used}
  \item{Residuals}{The residuals}
  \item{StdErrors}{Standard error estimates. Stored in column effect
    then row effect order}
}
\details{
  These functions fit row-column models to the specified input
  matrix. Specifically the model \deqn{y_{ij} = r_i + c_j +
    \epsilon_{ij}}{y_ij = r_i + c_j + e_ij}
       with \eqn{r_i} and \eqn{c_j} as row and column effects
       respectively. Note that these functions treat the row effect as
       the parameter to be constrained using sum to zero.

       The \code{rcModelPLMr} and \code{rcModelWPLMr} functions use 
       the PLM-r fitting procedure. This adds column and row robustness to single element robustness.

       The \code{rcModelPLMrc} and \code{rcModelWPLMrc} functions use 
       the PLM-rc fitting procedure. This adds column robustness to single element robustness.

       The \code{rcModelPLMrr} and \code{rcModelWPLMrr} functions use 
       the PLM-rr fitting procedure. This adds row robustness to single element robustness.


}
\seealso{
}
\examples{
col.effects <- c(10,11,10.5,12,9.5)
row.effects <- c(seq(-0.5,-0.1,by=0.1),seq(0.1,0.5,by=0.1))


y <- outer(row.effects, col.effects,"+")
w <- runif(50)

rcModelPLMr(y)
rcModelWPLMr(y, w)


### An example where there no or only occasional outliers
y <- y + rnorm(50,sd=0.1)
par(mfrow=c(2,2))
image(1:10,1:5,rcModelPLMr(y)$Weights,xlab="row",ylab="col",main="PLM-r",zlim=c(0,1))
image(1:10,1:5,rcModelPLMrc(y)$Weights,xlab="row",ylab="col",main="PLM-rc",zlim=c(0,1))
image(1:10,1:5,rcModelPLMrr(y)$Weights,xlab="row",ylab="col",main="PLM-rr",zlim=c(0,1))
matplot(y,type="l")


### An example where there is a row outlier
y <- outer(row.effects, col.effects,"+")
y[1,] <- 11+ rnorm(5)

y <- y + rnorm(50,sd=0.1)

par(mfrow=c(2,2))
image(1:10,1:5,rcModelPLMr(y)$Weights,xlab="row",ylab="col",main="PLM-r",zlim=c(0,1))
image(1:10,1:5,rcModelPLMrc(y)$Weights,xlab="row",ylab="col",main="PLM-rc",zlim=c(0,1))
image(1:10,1:5,rcModelPLMrr(y)$Weights,xlab="row",ylab="col",main="PLM-rr",zlim=c(0,1))
matplot(y,type="l")

### An example where there is a column outlier
y <- outer(row.effects, col.effects,"+")
w <- rep(1,50)

y[,4] <- 12 + rnorm(10)
y <- y + rnorm(50,sd=0.1)

par(mfrow=c(2,2))
image(1:10,1:5,rcModelWPLMr(y,w)$Weights,xlab="row",ylab="col",main="PLM-r",zlim=c(0,1))
image(1:10,1:5,rcModelWPLMrc(y,w)$Weights,xlab="row",ylab="col",main="PLM-rc",zlim=c(0,1))
image(1:10,1:5,rcModelWPLMrr(y,w)$Weights,xlab="row",ylab="col",main="PLM-rr",zlim=c(0,1))
matplot(y,type="l")


### An example where there is both column and row outliers
y <- outer(row.effects, col.effects,"+")
w <- rep(1,50)

y[,4] <- 12 + rnorm(10)
y[1,] <- 11+ rnorm(5)

y <- y + rnorm(50,sd=0.1)

par(mfrow=c(2,2))
image(1:10,1:5,rcModelWPLMr(y,w)$Weights,xlab="row",ylab="col",main="PLM-r",zlim=c(0,1))
image(1:10,1:5,rcModelWPLMrc(y,w)$Weights,xlab="row",ylab="col",main="PLM-rc",zlim=c(0,1))
image(1:10,1:5,rcModelWPLMrr(y,w)$Weights,xlab="row",ylab="col",main="PLM-rr",zlim=c(0,1))
matplot(y,type="l")

}
\author{B. M. Bolstad \email{bmb@bmbolstad.com}}
\keyword{models}