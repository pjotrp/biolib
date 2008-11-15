\name{subColSummarize}
\alias{subColSummarizeAvg}
\alias{subColSummarizeAvgLog}
\alias{subColSummarizeBiweight}
\alias{subColSummarizeBiweightLog}
\alias{subColSummarizeLogAvg}
\alias{subColSummarizeLogMedian}
\alias{subColSummarizeMedian}
\alias{subColSummarizeMedianLog}
\alias{subColSummarizeMedianpolish}
\alias{subColSummarizeMedianpolishLog}
\alias{convert.group.labels}
\title{Summarize columns when divided into groups of rows}
\description{These functions summarize columns of a matrix when the rows
  of the matrix are classified into different groups
}
\usage{subColSummarizeAvg(y, group.labels)
       subColSummarizeAvgLog(y, group.labels)
       subColSummarizeBiweight(y, group.labels)
       subColSummarizeBiweightLog(y, group.labels)
       subColSummarizeLogAvg(y, group.labels)
       subColSummarizeLogMedian(y, group.labels)
       subColSummarizeMedian(y, group.labels)
       subColSummarizeMedianLog(y, group.labels)
       subColSummarizeMedianpolish(y, group.labels)
       subColSummarizeMedianpolishLog(y, group.labels)
       convert.group.labels(group.labels)
}
\arguments{
  \item{y}{A numeric \code{\link{matrix}}}
  \item{group.labels}{A vector to be treated as a factor variable. This
    is used to assign each row to a group. NA values should be used to
    exclude rows from consideration}
}
\value{
  A \code{\link{matrix}} containing column summarized data. Each row
  corresponds to data column summarized over a group of rows.
}
\details{
  These functions are designed to summarize the columns of a matrix
  where the rows of the matrix are assigned to groups. The summarization
  is by column across all rows in each group.
  \itemize{
    \item{subColSummarizeAvg}{Summarize by taking mean}
    \item{subColSummarizeAvgLog}{\code{log2} transform the data and
      then take means in column-wise manner}
    \item{subColSummarizeBiweight}{Use a one-step Tukey Biweight to
      summarize columns}
    \item{subColSummarizeBiweightLog}{\code{log2} transform the data and
      then use a one-step Tukey Biweight to
      summarize columns}
    \item{subColSummarizeLogAvg}{Summarize by taking mean and then
      taking \code{log2}}
    \item{subColSummarizeLogMedian}{Summarize by taking median and then
      taking \code{log2}}
    \item{subColSummarizeMedian}{Summarize by taking median}
    \item{subColSummarizeMedianLog}{\code{log2} transform the data and
      then summarize by taking median}
    \item{subColSummarizeMedianpolish}{Use the median polish to
      summarize each column, by also using a row effect (not returned)}
    \item{subColSummarizeMedianpolishLog}{\code{log2} transform the
      data and then use the median polish to summarize each column, by
      also using a row effect (not returned)}
  }
  
}
\examples{
### Assign the first 10 rows to one group and
### the second 10 rows to the second group
###
y <- matrix(c(10+rnorm(50),20+rnorm(50)),20,5,byrow=TRUE)

subColSummarizeAvgLog(y,c(rep(1,10),rep(2,10)))
subColSummarizeLogAvg(y,c(rep(1,10),rep(2,10)))
subColSummarizeAvg(y,c(rep(1,10),rep(2,10)))

subColSummarizeBiweight(y,c(rep(1,10),rep(2,10)))
subColSummarizeBiweightLog(y,c(rep(1,10),rep(2,10)))

subColSummarizeMedianLog(y,c(rep(1,10),rep(2,10)))
subColSummarizeLogMedian(y,c(rep(1,10),rep(2,10)))
subColSummarizeMedian(y,c(rep(1,10),rep(2,10)))



subColSummarizeMedianpolishLog(y,c(rep(1,10),rep(2,10)))
subColSummarizeMedianpolish(y,c(rep(1,10),rep(2,10)))




}
\author{B. M. Bolstad <bmb@bmbolstad.com>}
\keyword{univar}