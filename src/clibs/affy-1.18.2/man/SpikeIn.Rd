\name{SpikeIn}
\alias{SpikeIn}
\alias{concentrations}
\title{SpikeIn Experiment Data: ProbeSet Example}
\description{
This \code{\link[affy:ProbeSet-class]{ProbeSet}} represents part of SpikeIn experiment
data set. 
}
\usage{data(SpikeIn)}
\format{\code{SpikeIn} is \code{\link[affy:ProbeSet-class]{ProbeSet}} containing the
  $PM$ and $MM$ intensities for a gene spiked in at different
  concentrations (given in the vector \code{colnames(pm(SpikeIn))}) in 12
  different arrays.}
\source{This comes from an experiments where 11 different cRNA
fragments have been added to the hybridization mixture of the GeneChip
arrays at different pM concentrations.  The 11 control cRNAs were BioB-5,
BioB-M, BioB-3, BioC-5, BioC-3, BioDn-5 (all {\it E. coli}), CreX-5, CreX-3
(phage P1), and  DapX-5, DapX-M, DapX-3 ({\it B. subtilis})
The cRNA were chosen to match the target sequence for each of the
Affymetrix control probe sets. For example, for DapX (a {\it B. subtilis}
gene), the 5', middle and 3' target sequences (identified by DapX-5,
DapX-M, DapX-3) were each synthesized separately and spiked-in at a
specific concentration. Thus, for example, DapX-3 target sequence may be
added to the total hybridization solution of 200 $\mu$l to give a final
concentration of 0.5 pM.

For this example we have the $PM$ and $MM$ for BioB-5
obtained from the arrays where it was spiked in at
0.0, 0.5, 0.75, 1, 1.5, 2, 3, 5, 12.5, 25, 50, and 150
pM.

For more information see Irizarry, R.A., et al. (2001)
\url{http://biosun01.biostat.jhsph.edu/~ririzarr/papers/index.html}}

\keyword{datasets}
