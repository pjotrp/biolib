%module bpptest
%{
#include "RASTools.h"
using namespace bpp;
%}
%include "DiscreteRatesAcrossSitesTreeLikelihood.i"
%include "DiscreteDistribution.i"

class RASTools
{
 public:
    static DiscreteDistribution * getPosteriorRateDistribution(const DiscreteRatesAcrossSitesTreeLikelihood & treeLikelihood);
};
