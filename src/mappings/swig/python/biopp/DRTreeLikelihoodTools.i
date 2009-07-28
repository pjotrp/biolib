%module bpptest
%{
#include "DRTreeLikelihoodTools.h"
using namespace bpp;
%}
%include "DRTreeLikelihood.i"
%include "AlignedSequenceContainer.i"

class DRTreeLikelihoodTools
{
  public:
    static VVVdouble getPosteriorProbabilitiesForEachStateForEachRate(const DRTreeLikelihood & drl, int nodeId);
};
