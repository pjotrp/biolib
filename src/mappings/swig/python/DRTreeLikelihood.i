%module bpptest
%{
#include "DRTreeLikelihood.h"
using namespace bpp;
%}
%include "AbstractNonHomogeneousTreeLikelihood.i"
%include "DRASDRTreeLikelihoodData.i"
%include "VectorTools.i"
%include "DiscreteDistribution.i"

class DRTreeLikelihood:public virtual DiscreteRatesAcrossSitesTreeLikelihood
{
  public:
    DRTreeLikelihood();
    virtual ~DRTreeLikelihood();
    DRTreeLikelihood* clone() const = 0;

    virtual DRASDRTreeLikelihoodData * getLikelihoodData() = 0;
    virtual const DRASDRTreeLikelihoodData * getLikelihoodData() const = 0;
    virtual void computeLikelihoodAtNode(int nodeId, VVVdouble& likelihoodArray) const = 0;
};
