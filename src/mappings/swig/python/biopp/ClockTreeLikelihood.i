%module bpptest
%{
#include "ClockTreeLikelihood.h"
using namespace bpp;
%}
%include "TreeLikelihood.i"
%include "DiscreteRatesAcrossSitesTreeLikelihood.i"
%include "TreeTemplate.i"
%include "ParameterList.i"

%ignore ClockTreeLikelihood::ClockTreeLikelihood;
%ignore ClockTreeLikelihood::~ClockTreeLikelihood;

class ClockTreeLikelihood:public virtual TreeLikelihood
{
  public:
    ClockTreeLikelihood * clone() const = 0;
    virtual ~ClockTreeLikelihood();
};

%ignore DiscreteRatesAcrossSitesClockTreeLikelihood::DiscreteRatesAcrossSitesClockTreeLikelihood;
%ignore DiscreteRatesAcrossSitesClockTreeLikelihood::~DiscreteRatesAcrossSitesClockTreeLikelihood;

class DiscreteRatesAcrossSitesClockTreeLikelihood:public virtual ClockTreeLikelihood,public virtual DiscreteRatesAcrossSitesTreeLikelihood
{
  public:
    DiscreteRatesAcrossSitesClockTreeLikelihood * clone() const = 0;
    virtual ~DiscreteRatesAcrossSitesClockTreeLikelihood();
};
