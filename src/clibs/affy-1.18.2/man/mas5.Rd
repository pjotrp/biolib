\name{mas5}
\alias{mas5}
\title{MAS 5.0 expression measure}
\description{
  This function converts an instance of \code{\link{AffyBatch}}
  into an instance of \code{\link[Biobase:class.ExpressionSet]{ExpressionSet}} using
  our implementation of Affymetrix's MAS 5.0 expression measure.
}
\usage{
mas5(object, normalize = TRUE, sc = 500, analysis = "absolute", ...)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{object}{an instance of \code{\link{AffyBatch}}}
  \item{normalize}{logical. If \code{TRUE} scale normalization is used
    after we obtain an instance of \code{\link[Biobase:class.ExpressionSet]{ExpressionSet}}}
  \item{sc}{Value at which all arrays will be scaled to.}
  \item{analysis}{should we do absolute or comparison analysis, although
    "comparison" is still not implemented.}
  \item{\dots}{other arguments to be passed to \code{\link{expresso}}.}
}
\details{
  This function is a wrapper for  \code{\link{expresso}} and \code{\link{affy.scalevalue.exprSet}}.}
\value{
  \code{\link[Biobase:class.ExpressionSet]{ExpressionSet}} 


  The methods used by this function
  were implemented based upon available documentation. In
  particular a useful reference is Statistical Algorithms Description
  Document by Affymetrix.
  Our implementation is based on what is written
  in the documentation and as you might appreciate there are places
  where the documentation is less than clear. This function does not
  give exactly the same results.
  All source code of our implementation is available. You are free to
  read it and suggest fixes. 

  For more information visit this URL:
  http://stat-www.berkeley.edu/users/bolstad/
    
}
\seealso{\code{\link{expresso}},\code{\link{affy.scalevalue.exprSet}}}
\examples{
  data(affybatch.example)
  eset <- mas5(affybatch.example)
}
\keyword{manip}% at least one, from doc/KEYWORDS

