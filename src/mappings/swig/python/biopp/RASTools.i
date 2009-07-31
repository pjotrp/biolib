%module bpptest
%{
#include "RASTools.h"
using namespace bpp;
%}
%include "DiscreteRatesAcrossSitesTreeLikelihood.i"
%include "DiscreteDistribution.i"

%ignore RASTools::RASTools;
%ignore RASTools::~RASTools;

class RASTools
{
 public:
    static DiscreteDistribution * getPosteriorRateDistribution(const DiscreteRatesAcrossSitesTreeLikelihood & treeLikelihood);
};
