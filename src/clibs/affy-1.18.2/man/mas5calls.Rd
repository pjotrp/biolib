\name{mas5calls}
\alias{mas5calls,AffyBatch-method}
\alias{mas5calls,ProbeSet-method}
\alias{mas5calls}
\alias{mas5.detection}
\alias{mas5calls.AffyBatch}
\alias{mas5calls.ProbeSet}
%- Also NEED an '\alias' for EACH other topic documented here.
\title{MAS 5.0 Absolute Detection}
\description{
 Performs the Wilcoxon signed rank-based gene expression presence/absence 
 detection algorithm first implemented in the Affymetrix Microarray Suite
 version 5.
}
\usage{
mas5calls(object,...)

mas5calls.AffyBatch(object, ids = NULL, verbose = TRUE, tau = 0.015,
                    alpha1 = 0.04, alpha2 = 0.06,
                    ignore.saturated=TRUE) 

mas5calls.ProbeSet(object, tau = 0.015, alpha1 = 0.04, alpha2 = 0.06,
                   ignore.saturated=TRUE) 

mas5.detection(mat, tau = 0.015, alpha1 = 0.04, alpha2 = 0.06,
               exact.pvals = FALSE, cont.correct = FALSE)
}
%- maybe also 'usage' for other objects documented here.
\arguments{
  \item{object}{An object of class \code{AffyBatch} or \code{ProbeSet}}
  \item{ids}{probeset IDs for which you want to compute calls}
  \item{mat}{an n-by-2 matrix of paired values (pairs in rows), PMs first col}
  \item{verbose}{logical. It \code{TRUE} status of processing is reported}
  \item{tau}{a small positive constant }
  \item{alpha1}{a significance threshold in (0,alph2)}
  \item{alpha2}{a significance threshold in (alpha1,0.5) }
  \item{exact.pvals}{a boolean controlling whether exact p-values are computed
    (irrelevant if n<50 and there are no ties).  Otherwise the
    normal approximation is used}
  \item{ignore.saturated}{ if true do the saturation correction described in the paper, with a saturation level of 46000 }
  \item{cont.correct}{a boolean controlling whether continuity
    correction is used in the p-value normal approximation  }
  \item{...}{any of the above arguments that applies}
    
}
\details{
 This function performs the hypothesis test:

  H0: median(Ri) = tau, corresponding to absence of transcript
  H1: median(Ri) > tau, corresponding to presence of transcript

where Ri = (PMi - MMi) / (PMi + MMi) for each i a probe-pair in the 
probe-set represented by data.

Currently exact.pvals=TRUE is not supported, and cont.correct=TRUE works but
 does not give great results (so both should be left as FALSE).  The defaults
 for tau, alpha1 and alpha2 correspond to those in MAS5.0.

 The p-value that is returned estimates the usual quantity:

   Pr(observing a more "present looking" probe-set than data | data is absent)

 So that small p-values imply presence while large ones imply absence of 
 transcript.  The detection call is computed by thresholding the p-value as 
 in:

 call "P" if p-value < alpha1
 call "M" if alpha1 <= p-value < alpha2
 call "A" if alpha2 <= p-value

 This implementation has been validated against the original MAS5.0
 implementation with the following results (for exact.pvals and cont.correct
 set to F):

   Average Relative Change from MAS5.0 p-values:38\%
   Proportion of calls different to MAS5.0 calls:1.0\%

 where "average/proportion" means over all probe-sets and arrays, where 
 the data came from 11 bacterial control probe-sets spiked-in over a range
 of concentrations (from 0 to 150 pico-mols) over 26 arrays.  These are
 the spike-in data from the GeneLogic Concentration Series Spikein Dataset.

 Clearly the p-values computed here differ from those computed by MAS5.0 --
 this will be improved in subsequent releases of the affy package.   However
 the p-value discrepancies are small enough to result in the call being very
 closely aligned with those of MAS5.0 (99 percent
 were identical on the validation
 set) -- so this implementation will still be of use.
 
The function \code{mas5.detect} is no longer the engine function for the
others. C code is no available that computes the wilcox test faster. THe
function is kept so that people can look at the R code (instead of C)
}

\value{
  \code{mas5.detect} returns a list containing the following components:
  \item{pval}{	a real p-value in [0,1] equal to the probability of
    observing probe-level intensities that are more present looking than
    data assuming the data represents an absent transcript; that is a
    transcript is more likely to be present for p-values closer 0.} 
  \item{call}{either "P", "M" or "A" representing a call of present,
    marginal or absent; computed by simply thresholding pval using
    alpha1 and}

  The \code{mas5calls} method for \code{AffyBatch} returns an
  \code{ExpressionSet} with calls accessible with \code{exprs(obj)}
  and p-values available with \code{assayData(obj)[["se.exprs"]]}. The
  code{mas5calls} for \code{ProbeSet} returns a list with vectors of calls
  and pvalues.
}

\references{

Liu, W. M. and Mei, R. and Di, X. and Ryder, T. B. and Hubbell, E. and Dee,
S. and Webster, T. A. and Harrington, C. A. and Ho, M. H. and Baid, J. and
Smeekens, S. P. (2002) Analysis of high density expression microarrays with
signed-rank call algorithms, Bioinformatics, 18(12), pp. 1593--1599.

Liu, W. and Mei, R. and Bartell, D. M. and Di, X. and Webster, T. A. and
Ryder, T. (2001) Rank-based algorithms for analysis of microarrays,
Proceedings of SPIE, Microarrays: Optical Technologies and Informatics, 4266.

Affymetrix (2002) Statistical Algorithms Description Document, Affymetrix
Inc., Santa Clara, CA,
whitepaper.
\url{http://www.affymetrix.com/support/technical/whitepapers/sadd_whitepaper.pdf},
\url{http://www.affymetrix.com/support/technical/whitepapers/sadd_whitepaper.pdf}
}
\author{Crispin Miller, Benjamin I. P. Rubinstein, Rafael A. Irizarry}
\examples{

data(affybatch.example)
PACalls <- mas5calls(affybatch.example)
}
\keyword{manip}
