\name{rcModelPLMd}
\alias{rcModelPLMd}

\title{Fit robust row-column models to a matrix}
\description{These functions fit row-column effect models to matrices using PLM-d}
\usage{
rcModelPLMd(y,group.labels)
}
\arguments{
  \item{y}{A numeric matrix}
  \item{group.labels}{A vector of group labels. Of length \code{ncol(y)}}
}
\value{
  A list with following items:
  \item{Estimates}{The parameter estimates. Stored in column effect then
    row effect order}
  \item{Weights}{The final weights used}
  \item{Residuals}{The residuals}
  \item{StdErrors}{Standard error estimates. Stored in column effect
    then row effect order}
  \item{WasSplit}{An indicator variable indicating whether or not a row was
  split with separate row effects for each group}
}
\details{
  This functions first tries to fit row-column models to the specified input
  matrix. Specifically the model \deqn{y_{ij} = r_i + c_j +
    \epsilon_{ij}}{y_ij = r_i + c_j + e_ij}
       with \eqn{r_i} and \eqn{c_j} as row and column effects
       respectively. Note that these functions treat the row effect as
       the parameter to be constrained using sum to zero.

  Next the residuals for each row are compared to the group variable. In cases
  where there appears to be a significant relationship, the row-effect is "split" and separate row-effect parameters, one for each group, replace the single row effect.
}
\seealso{
}
\examples{
col.effects <- c(10,11,10.5,12,9.5)
row.effects <- c(seq(-0.5,-0.1,by=0.1),seq(0.1,0.5,by=0.1))


y <- outer(row.effects, col.effects,"+")
y <- y + rnorm(50,sd=0.1)

rcModelPLMd(y,group.labels=c(1,1,2,2,2))


row.effects <- c(4,3,2,1,-1,-2,-3,-4)
col.effects  <- c(8,9,10,11,12,10)

y <- outer(row.effects, col.effects,"+") + rnorm(48,0,0.25)

y[8,4:6] <- c(11,12,10)+ 2.5 + rnorm(3,0,0.25)
y[5,4:6] <- c(11,12,10)+-2.5 + rnorm(3,0,0.25)


rcModelPLMd(y,group.labels=c(1,1,1,2,2,2))

par(mfrow=c(2,2))
matplot(y,type="l",col=c(rep("red",3),rep("blue",3)),ylab="residuals",xlab="probe",main="Observed Data")
matplot(rcModelPLM(y)$Residuals,col=c(rep("red",3),rep("blue",3)),ylab="residuals",xlab="probe",main="Residuals (PLM)")
matplot(rcModelPLMd(y,group.labels=c(1,1,1,2,2,2))$Residuals,col=c(rep("red",3),rep("blue",3)),xlab="probe",ylab="residuals",main="Residuals (PLM-d)")

}
\author{B. M. Bolstad \email{bmb@bmbolstad.com}}
\keyword{models}