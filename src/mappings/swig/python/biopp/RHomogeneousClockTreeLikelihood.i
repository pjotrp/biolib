%module bpptest
%{
#include "RHomogeneousClockTreeLikelihood.h"
using namespace bpp;
%}
%include "RHomogeneousTreeLikelihood.i"
%include "ClockTreeLikelihood.i"
%include "TreeTemplate.i"
%include "ParameterList.i"

class RHomogeneousClockTreeLikelihood:public RHomogeneousTreeLikelihood,public DiscreteRatesAcrossSitesClockTreeLikelihood
{
  public:
    RHomogeneousClockTreeLikelihood(const Tree & tree,SubstitutionModel * model,DiscreteDistribution * rDist,bool checkRooted = true,bool verbose = true) throw (Exception);
    RHomogeneousClockTreeLikelihood(const Tree & tree,const SiteContainer & data,SubstitutionModel * model,DiscreteDistribution * rDist,bool checkRooted = true,bool verbose = true) throw (Exception);
    RHomogeneousClockTreeLikelihood* clone() const;
    virtual ~RHomogeneousClockTreeLikelihood();

    void applyParameters() throw (Exception);
    void fireParameterChanged(const ParameterList& params);
    void initBranchLengthsParameters();
    ParameterList getDerivableParameters() const throw (Exception);
    ParameterList getNonDerivableParameters() const throw (Exception);
    double getFirstOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable1, const string & variable2) const throw (Exception); 
};
