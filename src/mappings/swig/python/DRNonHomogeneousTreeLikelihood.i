%module bpptest
%{
#include "DRNonHomogeneousTreeLikelihood.h"
using namespace bpp;
%}
%include "AbstractNonHomogeneousTreeLikelihood.i"
%include "DRTreeLikelihood.i"
%include "DRASDRTreeLikelihoodData.i"
%include "VectorTools.i"
%include "DiscreteDistribution.i"

%rename(__assign__) DRNonHomogeneousTreeLikelihood::operator=;

class DRNonHomogeneousTreeLikelihood:public AbstractNonHomogeneousTreeLikelihood,public DRTreeLikelihood
{
  public:
    DRNonHomogeneousTreeLikelihood(const Tree & tree, SubstitutionModelSet * modelSet, DiscreteDistribution * rDist, bool verbose = true) throw (Exception);
    DRNonHomogeneousTreeLikelihood(const Tree & tree, const SiteContainer & data, SubstitutionModelSet * modelSet, DiscreteDistribution * rDist, bool verbose = true) throw (Exception);
    DRNonHomogeneousTreeLikelihood(const DRNonHomogeneousTreeLikelihood & lik);
    DRNonHomogeneousTreeLikelihood & operator=(const DRNonHomogeneousTreeLikelihood & lik);
    virtual ~DRNonHomogeneousTreeLikelihood();
    DRNonHomogeneousTreeLikelihood* clone() const;

    void setData(const SiteContainer & sites) throw (Exception);
    double getLikelihood () const;
    double getLogLikelihood() const;
    double getLikelihoodForASite (unsigned int site) const;
    double getLogLikelihoodForASite(unsigned int site) const;      
    void computeTreeLikelihood();
    double getLikelihoodForASiteForARateClass(unsigned int site, unsigned int rateClass) const;
    double getLogLikelihoodForASiteForARateClass(unsigned int site, unsigned int rateClass) const;
    double getLikelihoodForASiteForARateClassForAState(unsigned int site, unsigned int rateClass, int state) const;
    double getLogLikelihoodForASiteForARateClassForAState(unsigned int site, unsigned int rateClass, int state) const;
    void setParameters(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    double getValue() const throw (Exception);
    double getFirstOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable1, const string & variable2) const throw (Exception); 

    DRASDRTreeLikelihoodData * getLikelihoodData();
    const DRASDRTreeLikelihoodData * getLikelihoodData() const;
    virtual void computeLikelihoodAtNode(int nodeId, VVVdouble& likelihoodArray) const;
};
