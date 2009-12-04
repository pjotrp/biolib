\name{colSumamrize}
\alias{colSummarizeAvg}
\alias{colSummarizeAvgLog}
\alias{colSummarizeBiweight}
\alias{colSummarizeBiweightLog}
\alias{colSummarizeLogAvg}
\alias{colSummarizeLogMedian}
\alias{colSummarizeMedian}
\alias{colSummarizeMedianLog}
\alias{colSummarizeMedianpolish}
\alias{colSummarizeMedianpolishLog}

\title{Summarize the column of matrices}
\description{Compute column wise summary values of a matrix.
}
\usage{
colSummarizeAvg(y)
colSummarizeAvgLog(y)
colSummarizeBiweight(y)
colSummarizeBiweightLog(y)
colSummarizeLogAvg(y)
colSummarizeLogMedian(y)
colSummarizeMedian(y)
colSummarizeMedianLog(y)
colSummarizeMedianpolish(y)
colSummarizeMedianpolishLog(y)

}
\arguments{
  \item{y}{A numeric matrix}
}
\value{
  A list with following items:
  \item{Estimates}{Summary values for each column.}
  \item{StdErrors}{Standard error estimates.}
}
\details{This groups of functions summarize the columns of a given
  matrices.

  \itemize{
    \item{\code{colSummarizeAvg}}{Take means in column-wise manner}
    \item{\code{colSummarizeAvgLog}}{\code{log2} transform the data and
      then take means in column-wise manner}
    \item{\code{colSummarizeBiweight}}{Summarize each column using a one
      step Tukey Biweight procedure}
    \item{\code{colSummarizeBiweightLog}}{\code{log2} transform the data
      and then summarize each column using a one step Tuke Biweight
      procedure}
    \item{\code{colSummarizeLogAvg}}{Compute the mean of each column and
      then \code{log2} transform it}
    \item{\code{colSummarizeLogMedian}}{Compute the median of each
      column and then \code{log2} transform it}
    \item{\code{colSummarizeMedian}}{Compute the median of each column}
    \item{\code{colSummarizeMedianLog}}{\code{log2} transform the data
      and then summarize each column using the median}
    \item{\code{colSummarizeMedianpolish}}{Use the median polish to
      summarize each column, by also using a row effect (not returned)}
    \item{\code{colSummarizeMedianpolishLog}}{\code{log2} transform the
      data and then use the median polish to summarize each column, by
      also using a row effect (not returned)}
  }
}
\examples{
y <- matrix(10+rnorm(100),20,5)

colSummarizeAvg(y)
colSummarizeAvgLog(y)
colSummarizeBiweight(y)
colSummarizeBiweightLog(y)
colSummarizeLogAvg(y)
colSummarizeLogMedian(y)
colSummarizeMedian(y)
colSummarizeMedianLog(y)
colSummarizeMedianpolish(y)
colSummarizeMedianpolishLog(y)
}
\author{B. M. Bolstad   \email{bmb@bmbolstad.com}}
\keyword{univar}