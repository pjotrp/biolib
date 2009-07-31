%module bpptest
%{
#include "DiscreteRatesAcrossSitesTreeLikelihood.h"
using namespace bpp;
%}
%include "TreeLikelihood.i"
%include "DiscreteDistribution.i"
%include "ParameterList.i"

%ignore DiscreteRatesAcrossSitesTreeLikelihood::DiscreteRatesAcrossSitesTreeLikelihood;
%ignore DiscreteRatesAcrossSitesTreeLikelihood::~DiscreteRatesAcrossSitesTreeLikelihood;

class DiscreteRatesAcrossSitesTreeLikelihood:public virtual TreeLikelihood
{
  public:
    DiscreteRatesAcrossSitesTreeLikelihood();
    virtual ~DiscreteRatesAcrossSitesTreeLikelihood();

    virtual const DiscreteDistribution * getRateDistribution() const = 0;
    virtual DiscreteDistribution * getRateDistribution() = 0;
    virtual double getLikelihoodForASiteForARateClass(unsigned int site, unsigned int rateClass) const = 0;
    virtual double getLogLikelihoodForASiteForARateClass(unsigned int site, unsigned int rateClass) const = 0;
    virtual double getLikelihoodForASiteForARateClassForAState(unsigned int site, unsigned int rateClass, int state) const = 0;
    virtual double getLogLikelihoodForASiteForARateClassForAState(unsigned int site, unsigned int rateClass, int state) const = 0;
    virtual VVdouble getLikelihoodForEachSiteForEachRateClass() const = 0;
    virtual VVdouble getLogLikelihoodForEachSiteForEachRateClass() const = 0;
    virtual VVVdouble getLikelihoodForEachSiteForEachRateClassForEachState() const = 0;
    virtual VVVdouble getLogLikelihoodForEachSiteForEachRateClassForEachState() const = 0;
    virtual VVdouble getPosteriorProbabilitiesOfEachRate() const = 0;
    virtual vector<unsigned int> getRateClassWithMaxPostProbOfEachSite() const = 0;
    virtual Vdouble getRateWithMaxPostProbOfEachSite() const = 0;
    virtual Vdouble getPosteriorRateOfEachSite() const = 0;
    virtual ParameterList getRateDistributionParameters() const = 0;
    virtual unsigned int getNumberOfClasses() const = 0;
};
