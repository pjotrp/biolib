\name{ProgressBarText-class}
\docType{class}
\alias{ProgressBarText-class}
\alias{close,ProgressBarText-method}
\alias{initialize,ProgressBarText-method}
\alias{open,ProgressBarText-method}
\alias{update,ProgressBarText-method}

\title{Class "ProgressBarText" }
\description{ A class to handle progress bars in text mode}
\section{Objects from the Class}{
Objects can be created by calls of the form \code{new("ProgressBarText", steps)}.
}
\section{Slots}{
  \describe{
    \item{\code{steps}:}{Object of class \code{"integer"}. The total number of
      steps the progress bar should represent}
    \item{\code{barsteps}:}{Object of class \code{"integer"}. The size
      of the progress bar.}
    \item{\code{internals}:}{Object of class \code{"environment"}. For internal use.}
  }
}
\section{Methods}{
  \describe{
    \item{close}{\code{signature(con = "ProgressBarText")}: Terminate
      the progress bar (i.e. print what needs to be printed). Note that
      closing the instance will ensure the progress bar is plotted to
      its end.}
    \item{initialize}{\code{signature(.Object = "ProgressBarText")}:
      initialize a instance.}
    \item{open}{\code{signature(con = "ProgressBarText")}: Open a
      progress bar (i.e. print things). In the case open is called on
      a progress bar that was 'progress', the progress bar is resumed
      (this might be useful when one wishes to insert text output while
      there is a progress bar running).}
    \item{update}{\code{signature(object = "ProgressBarText")}: Update
      the progress bar (see examples).}
  }
}
\author{ Laurent }
\examples{
f <- function(x, header = TRUE) {
  pbt <- new("ProgressBarText", length(x), barsteps = as.integer(20))

  open(pbt, header = header)

  for (i in x) {
    Sys.sleep(i)
    update(pbt)
  }
  close(pbt)
}

## if too fast on your machine, change the number
x <- runif(15)

f(x)
f(x, header = FALSE)

## 'cost' of the progress bar:
g <- function(x) {
  z <- 1
  for (i in 1:x) {
    z <- z + 1
  }
}
h <- function(x) {
  pbt <- new("ProgressBarText", as.integer(x), barsteps = as.integer(20))
  open(pbt)
  for (i in 1:x) {
    update(pbt)
  }
  close(pbt)
}

system.time(g(10000))
system.time(h(10000))

}
\keyword{classes}
