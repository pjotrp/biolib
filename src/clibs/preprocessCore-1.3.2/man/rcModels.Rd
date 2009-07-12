\name{rcModels}
\alias{rcModelPLM}
\alias{rcModelWPLM}
\alias{rcModelMedianPolish}
\title{Fit row-column model to a matrix}
\description{These functions fit row-column effect models to matrices
}
\usage{
rcModelPLM(y,row.effects=NULL)
rcModelWPLM(y, w,row.effects=NULL)
rcModelMedianPolish(y)
}
\arguments{
  \item{y}{A numeric matrix}
  \item{w}{A matrix or vector of weights. These should be non-negative.}
  \item{row.effects}{If these are supplied then the fitting procedure uses these (and analyzes individual columns separately)}
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
       respectively. Note that this functions treat the row effect as
       the parameter to be constrained using sum to zero (for
       \code{rcModelPLM} and \code{rcModelWPLM}) or median of zero (for
       \code{rcModelMedianPolish}).

       The \code{rcModelPLM} and \code{rcModelWPLM} functions use a
       robust linear model procedure for fitting the model.

       The function \code{rcModelMedianPolish} uses the median polish algorithm.
}
\seealso{
}
\examples{
col.effects <- c(10,11,10.5,12,9.5)
row.effects <- c(seq(-0.5,-0.1,by=0.1),seq(0.1,0.5,by=0.1))


y <- outer(row.effects, col.effects,"+")
w <- runif(50)

rcModelPLM(y)
rcModelWPLM(y, w)
rcModelMedianPolish(y)

y <- y + rnorm(50)

rcModelPLM(y)
rcModelWPLM(y, w)
rcModelMedianPolish(y)



rcModelPLM(y,row.effects=row.effects)
rcModelWPLM(y,w,row.effects=row.effects)

}
\author{B. M. Bolstad \email{bmb@bmbolstad.com}}
\keyword{models}