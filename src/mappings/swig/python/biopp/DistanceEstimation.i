%module bpptest
%{
#include "DistanceEstimation.h"
using namespace bpp;
%}
%include "SubstitutionModel.i"
%include "AbstractTreeLikelihood.i"
%include "DRHomogeneousTreeLikelihood.i"
%include "PseudoNewtonOptimizer.i"
%include "Clonable.i"
%include "ParameterList.i"
%include "DiscreteDistribution.i"
%include "Optimizer.i"
%include "SimpleMultiDimensions.i"
%include "MetaOptimizer.i"
%include "SiteContainer.i"

%rename(__assign__) TwoTreeLikelihood::operator=;

class TwoTreeLikelihood:public AbstractDiscreteRatesAcrossSitesTreeLikelihood  
{
  public:
    TwoTreeLikelihood(const string & seq1, const string & seq2,   const SiteContainer & data, SubstitutionModel * model, DiscreteDistribution * rDist, bool verbose) throw (Exception);
    TwoTreeLikelihood(const TwoTreeLikelihood & lik);
    TwoTreeLikelihood & operator=(const TwoTreeLikelihood & lik);
    TwoTreeLikelihood* clone() const; 
    virtual ~TwoTreeLikelihood();

    double getLikelihood () const;
    double getLogLikelihood() const;
    double getLikelihoodForASite (unsigned int site) const;
    double getLogLikelihoodForASite(unsigned int site) const;
    ParameterList getBranchLengthsParameters() const;
    ParameterList getSubstitutionModelParameters() const;
    SubstitutionModel * getSubstitutionModelForNode(int nodeId) throw (NodeNotFoundException);
    const SubstitutionModel * getSubstitutionModelForNode(int nodeId) const throw (NodeNotFoundException);
    vector<double> getRootFrequencies() const;
    const VVVdouble & getTransitionProbabilitiesForNode(const Node* node) const;
    void setData(const SiteContainer & sites) throw (Exception);
    void initialize() throw(Exception);
    double getLikelihoodForASiteForARateClass(unsigned int site, unsigned int rateClass) const;
    double getLogLikelihoodForASiteForARateClass(unsigned int site, unsigned int rateClass) const;
    double getLikelihoodForASiteForARateClassForAState(unsigned int site, unsigned int rateClass, int state) const;
    double getLogLikelihoodForASiteForARateClassForAState(unsigned int site, unsigned int rateClass, int state) const;
    virtual const SubstitutionModel * getSubstitutionModel() const;
    virtual SubstitutionModel * getSubstitutionModel();
    void setParameters(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    double getValue() const throw(Exception);
    double getFirstOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable1, const string & variable2) const throw (Exception); 
    virtual void initBranchLengthsParameters();
    virtual void setMinimumBranchLength(double minimum);
    virtual double getMinimumBranchLength() const;
};

%rename(__assign__) DistanceEstimation::operator=;

class DistanceEstimation:public virtual Clonable
{
  public:
    DistanceEstimation(SubstitutionModel * model, DiscreteDistribution * rateDist, const SiteContainer * sites, unsigned int verbose = 1, bool computeMat = true);
    DistanceEstimation(const DistanceEstimation & distanceEstimation);
    DistanceEstimation & operator=(const DistanceEstimation & distanceEstimation);
    virtual ~DistanceEstimation();
    DistanceEstimation * clone() const;

    void computeMatrix() throw (NullPointerException);
    DistanceMatrix * getMatrix() const;
    SubstitutionModel * getModel() const;
    void resetModel();
    DiscreteDistribution * getRateDistribution() const;
    void resetRateDistribution();
    void setData(const SiteContainer * sites);
    const SiteContainer * getData() const;
    void resetData();
    void setOptimizer(const Optimizer * optimizer);
    const Optimizer * getOptimizer() const;
    Optimizer * getOptimizer();
    void resetOptimizer();
    void setAdditionalParameters(const ParameterList & parameters);
    void resetAdditionalParameters();
    void setVerbose(unsigned int verbose);
    unsigned int getVerbose() const;
};
