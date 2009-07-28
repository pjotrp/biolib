%module bpptest
%{
#include "AbstractHomogeneousTreeLikelihood.h"
using namespace bpp;
%}
%include "AbstractDiscreteRatesAcrossSitesTreeLikelihood.i"
%include "HomogeneousTreeLikelihood.i"

%rename(__assign__) AbstractHomogeneousTreeLikelihood::operator=;

class AbstractHomogeneousTreeLikelihood:public virtual HomogeneousTreeLikelihood,public AbstractDiscreteRatesAcrossSitesTreeLikelihood
{
  public:
    AbstractHomogeneousTreeLikelihood(const Tree & tree, SubstitutionModel * model, DiscreteDistribution * rDist, bool checkRooted = true, bool verbose = true) throw (Exception);
    AbstractHomogeneousTreeLikelihood(const AbstractHomogeneousTreeLikelihood & lik);
    AbstractHomogeneousTreeLikelihood & operator=(const AbstractHomogeneousTreeLikelihood & lik);
    virtual ~AbstractHomogeneousTreeLikelihood();

    void initialize() throw(Exception);
    ParameterList getBranchLengthsParameters() const;
    ParameterList getSubstitutionModelParameters() const;
    ParameterList getRateDistributionParameters() const;
    const SubstitutionModel * getSubstitutionModelForNode(int nodeId) const throw (NodeNotFoundException);
    SubstitutionModel * getSubstitutionModelForNode(int nodeId) throw (NodeNotFoundException);
    vector<double> getRootFrequencies() const;
    const VVVdouble & getTransitionProbabilitiesForNode(const Node* node) const;
    const SubstitutionModel * getSubstitutionModel() const;
    SubstitutionModel * getSubstitutionModel();
    void setSubstitutionModel(SubstitutionModel * model) throw (Exception);

    virtual void initParameters();
    virtual void applyParameters() throw (Exception);  
    virtual void initBranchLengthsParameters();
    virtual void setMinimumBranchLength(double minimum);
    virtual double getMinimumBranchLength() const;
};
