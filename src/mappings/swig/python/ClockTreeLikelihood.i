%module bpptest
%{
#include "ClockTreeLikelihood.h"
using namespace bpp;
%}
%include "TreeLikelihood.i"
%include "DiscreteRatesAcrossSitesTreeLikelihood.i"
%include "TreeTemplate.i"
%include "ParameterList.i"

class ClockTreeLikelihood:public virtual TreeLikelihood
{
  public:
    ClockTreeLikelihood * clone() const = 0;
    virtual ~ClockTreeLikelihood();
};

class DiscreteRatesAcrossSitesClockTreeLikelihood:public virtual ClockTreeLikelihood,public virtual DiscreteRatesAcrossSitesTreeLikelihood
{
  public:
    DiscreteRatesAcrossSitesClockTreeLikelihood * clone() const = 0;
    virtual ~DiscreteRatesAcrossSitesClockTreeLikelihood();
};
