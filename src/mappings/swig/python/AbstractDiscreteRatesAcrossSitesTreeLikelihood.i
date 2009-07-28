%module bpptest
%{
#include "AbstractDiscreteRatesAcrossSitesTreeLikelihood.h"
using namespace bpp;
%}
%include "AbstractTreeLikelihood.i"
%include "DiscreteRatesAcrossSitesTreeLikelihood.i"
%include "SubstitutionModel.i"

class AbstractDiscreteRatesAcrossSitesTreeLikelihood:public AbstractTreeLikelihood,public virtual DiscreteRatesAcrossSitesTreeLikelihood
{
  public:
    AbstractDiscreteRatesAcrossSitesTreeLikelihood(DiscreteDistribution * rDist, bool verbose = true) throw (Exception);
    virtual ~AbstractDiscreteRatesAcrossSitesTreeLikelihood();

    double getLikelihoodForASiteForAState (unsigned int site, int state) const;
    double getLogLikelihoodForASiteForAState(unsigned int site, int state) const;
    ParameterList getDerivableParameters() const;
    ParameterList getNonDerivableParameters() const;
     
    const DiscreteDistribution * getRateDistribution() const;
    DiscreteDistribution * getRateDistribution();
    unsigned int getNumberOfClasses() const; 
    ParameterList getRateDistributionParameters() const;
    VVdouble getLikelihoodForEachSiteForEachRateClass() const;
    VVdouble getLogLikelihoodForEachSiteForEachRateClass() const;
    VVVdouble getLikelihoodForEachSiteForEachRateClassForEachState() const;
    VVVdouble getLogLikelihoodForEachSiteForEachRateClassForEachState() const;
    VVdouble getPosteriorProbabilitiesOfEachRate() const;
    Vdouble getRateWithMaxPostProbOfEachSite() const;
    vector<unsigned int> getRateClassWithMaxPostProbOfEachSite() const;
    Vdouble getPosteriorRateOfEachSite() const;
    static void resetLikelihoodArray(VVVdouble & likelihoodArray);
    static void displayLikelihoodArray(const VVVdouble & likelihoodArray);
};
