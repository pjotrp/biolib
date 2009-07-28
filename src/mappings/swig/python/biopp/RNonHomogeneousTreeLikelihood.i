%module bpptest
%{
#include "RNonHomogeneousTreeLikelihood.h"
using namespace bpp;
%}
%include "AbstractNonHomogeneousTreeLikelihood.i"
%include "SubstitutionModelSet.i"
%include "DRASRTreeLikelihoodData.i"
%include "VectorTools.i"
%include "DiscreteDistribution.i"

%rename(__assign__) RNonHomogeneousTreeLikelihood::operator=;

class RNonHomogeneousTreeLikelihood : public AbstractNonHomogeneousTreeLikelihood
{
  public:
    RNonHomogeneousTreeLikelihood(const Tree & tree,SubstitutionModelSet * modelSet,DiscreteDistribution * rDist,bool verbose = true, bool usePatterns = true) throw (Exception);
    RNonHomogeneousTreeLikelihood(const Tree & tree,const SiteContainer & data,SubstitutionModelSet * modelSet,DiscreteDistribution * rDist,bool verbose = true, bool usePatterns = true) throw (Exception);
    RNonHomogeneousTreeLikelihood(const RNonHomogeneousTreeLikelihood & lik);
    RNonHomogeneousTreeLikelihood & operator=(const RNonHomogeneousTreeLikelihood & lik);
    virtual ~RNonHomogeneousTreeLikelihood();
    RNonHomogeneousTreeLikelihood* clone() const;

    void setData(const SiteContainer & sites) throw (Exception);
    double getLikelihood () const;
    double getLogLikelihood() const;
    double getLikelihoodForASite (unsigned int site) const;
    double getLogLikelihoodForASite(unsigned int site) const;
     
    double getLikelihoodForASiteForARateClass(unsigned int site, unsigned int rateClass) const;
    double getLogLikelihoodForASiteForARateClass(unsigned int site, unsigned int rateClass) const;
    double getLikelihoodForASiteForARateClassForAState(unsigned int site, unsigned int rateClass, int state) const;
    double getLogLikelihoodForASiteForARateClassForAState(unsigned int site, unsigned int rateClass, int state) const;
    void setParameters(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    double getValue() const throw(Exception);
    double getFirstOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable1, const string & variable2) const throw (Exception); 

    DRASRTreeLikelihoodData * getLikelihoodData();
    const DRASRTreeLikelihoodData * getLikelihoodData() const;
    void computeTreeLikelihood();
    virtual double getDLikelihoodForASiteForARateClass(unsigned int site, unsigned int rateClass) const;
    virtual double getDLikelihoodForASite(unsigned int site) const;
    virtual double getDLogLikelihoodForASite(unsigned int site) const;
    virtual double getDLogLikelihood() const;
    virtual void computeTreeDLikelihood(const string & variable);
    virtual double getD2LikelihoodForASiteForARateClass(unsigned int site, unsigned int rateClass) const;
    virtual double getD2LikelihoodForASite(unsigned int site) const;
    virtual double getD2LogLikelihoodForASite(unsigned int site) const;
    virtual double getD2LogLikelihood() const;
    virtual void computeTreeD2Likelihood(const string & variable);
};
