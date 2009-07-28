%module bpptest
%{
#include "NNIHomogeneousTreeLikelihood.h"
using namespace bpp;
%}
%include "DRHomogeneousTreeLikelihood.i"
%include "NNISearchable.i"
%include "VectorTools.i"
%include "DiscreteDistribution.i"
%include "BrentOneDimension.i"
%include "Parametrizable.i"

class BranchLikelihood :public Function,public AbstractParametrizable
{
  public:
    BranchLikelihood(const vector<unsigned int> & weights);
    virtual ~BranchLikelihood();
    BranchLikelihood* clone() const;

    void initModel(const SubstitutionModel *model, const DiscreteDistribution *rDist);
    void initLikelihoods(const VVVdouble *array1, const VVVdouble *array2);
    void resetLikelihoods();
    void setParameters(const ParameterList &parameters) throw (ParameterNotFoundException, ConstraintException);
    double getValue() const throw (Exception);
    void fireParameterChanged(const ParameterList & parameters);
};

%rename(__assign__) NNIHomogeneousTreeLikelihood::operator=;

class NNIHomogeneousTreeLikelihood:public DRHomogeneousTreeLikelihood,public NNISearchable
{
  public:
    NNIHomogeneousTreeLikelihood(const Tree & tree,SubstitutionModel * model,DiscreteDistribution * rDist,bool checkRooted = true,bool verbose = true) throw (Exception);
    NNIHomogeneousTreeLikelihood(const Tree & tree,const SiteContainer & data,SubstitutionModel * model,DiscreteDistribution * rDist,bool checkRooted = true,bool verbose = true) throw (Exception);
    NNIHomogeneousTreeLikelihood(const NNIHomogeneousTreeLikelihood & lik);
    NNIHomogeneousTreeLikelihood & operator=(const NNIHomogeneousTreeLikelihood & lik);
    virtual ~NNIHomogeneousTreeLikelihood();
    NNIHomogeneousTreeLikelihood* clone() const;

    void setData(const SiteContainer & sites) throw (Exception);
    const Tree * getTopology() const;
    double getTopologyValue() const throw (Exception);
    double testNNI(int nodeId) const throw (NodeException);
    void doNNI(int nodeId) throw (NodeException);
    void topologyChangeTested(const TopologyChangeEvent & event);
    void topologyChangeSuccessful(const TopologyChangeEvent & event);
};
