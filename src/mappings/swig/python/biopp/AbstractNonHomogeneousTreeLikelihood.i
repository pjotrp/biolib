%module bpptest
%{
#include "AbstractNonHomogeneousTreeLikelihood.h"
using namespace bpp;
%}
%include "NonHomogeneousTreeLikelihood.i"
%include "AbstractDiscreteRatesAcrossSitesTreeLikelihood.i"

%rename(__assign__) AbstractNonHomogeneousTreeLikelihood::operator=;

class AbstractNonHomogeneousTreeLikelihood:public virtual NonHomogeneousTreeLikelihood,public AbstractDiscreteRatesAcrossSitesTreeLikelihood
{
  public:
    AbstractNonHomogeneousTreeLikelihood(const Tree & tree, SubstitutionModelSet * modelSet, DiscreteDistribution * rDist, bool verbose = true) throw (Exception);
    AbstractNonHomogeneousTreeLikelihood(const AbstractNonHomogeneousTreeLikelihood & lik);
    AbstractNonHomogeneousTreeLikelihood & operator=(const AbstractNonHomogeneousTreeLikelihood & lik);
    virtual ~AbstractNonHomogeneousTreeLikelihood();

    void initialize() throw(Exception);
    ParameterList getBranchLengthsParameters() const;
    ParameterList getSubstitutionModelParameters() const;
    ParameterList getRateDistributionParameters() const;
    const SubstitutionModel * getSubstitutionModelForNode(int nodeId) const throw (NodeNotFoundException);
    SubstitutionModel * getSubstitutionModelForNode(int nodeId) throw (NodeNotFoundException);
    vector<double> getRootFrequencies() const;
    const VVVdouble & getTransitionProbabilitiesForNode(const Node* node) const;
    const SubstitutionModelSet * getSubstitutionModelSet() const;
    SubstitutionModelSet * getSubstitutionModelSet();
    void setSubstitutionModelSet(SubstitutionModelSet * modelSet) throw (Exception);
    ParameterList getRootFrequenciesParameters() const;

    virtual void initParameters();
    virtual void applyParameters() throw (Exception);  
    virtual void initBranchLengthsParameters();
    virtual void setMinimumBranchLength(double minimum);
    virtual double getMinimumBranchLength() const;
};
