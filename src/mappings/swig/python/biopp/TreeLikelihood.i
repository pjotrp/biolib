%module bpptest
%{
#include "TreeLikelihood.h"
using namespace bpp;
%}
%include "Node.i"
%include "Tree.i"
%include "SubstitutionModel.i"
%include "ParameterList.i"
%include "Parametrizable.i"
%include "Functions.i"
%include "VectorTools.i"
%include "Alphabet.i"
%include "SiteContainer.i"

%ignore TreeLikelihood::TreeLikelihood;
%ignore TreeLikelihood::~TreeLikelihood;

class TreeLikelihood:public virtual DerivableSecondOrder
{
  public:
    TreeLikelihood();
    virtual ~TreeLikelihood();
    TreeLikelihood * clone() const = 0;

    virtual void setData(const SiteContainer & sites) = 0;
    virtual const SiteContainer * getData() const = 0;
    virtual void initialize() throw (Exception) = 0;
    virtual bool isInitialized() const = 0;
    virtual double getLikelihoodForASite(unsigned int site) const = 0;
    virtual double getLogLikelihoodForASite(unsigned int site) const = 0;
    virtual double getLikelihoodForASiteForAState(unsigned int site, int state) const = 0;
    virtual double getLogLikelihoodForASiteForAState(unsigned int site, int state) const = 0;
    virtual Vdouble getLikelihoodForEachSite() const = 0;
    virtual Vdouble getLogLikelihoodForEachSite() const = 0;
    virtual VVdouble getLikelihoodForEachSiteForEachState() const = 0;
    virtual VVdouble getLogLikelihoodForEachSiteForEachState() const = 0;
    virtual double getLikelihood() const = 0;
    virtual double getLogLikelihood() const = 0;
    virtual const Tree * getTree() const = 0;
    virtual unsigned int getNumberOfSites() const = 0;
    virtual unsigned int getNumberOfStates() const = 0;
    virtual const Alphabet * getAlphabet() const = 0;
    virtual ParameterList getBranchLengthsParameters() const = 0;
    virtual ParameterList getSubstitutionModelParameters() const = 0;
    virtual const SubstitutionModel * getSubstitutionModelForNode(int nodeId) const throw (NodeNotFoundException) = 0;
    virtual SubstitutionModel * getSubstitutionModelForNode(int nodeId) throw (NodeNotFoundException) = 0;
    virtual vector<double> getRootFrequencies() const = 0;
    virtual void enableDerivatives(bool yn) = 0;
    virtual ParameterList getDerivableParameters() const = 0;
    virtual ParameterList getNonDerivableParameters() const = 0;
    virtual const VVVdouble & getTransitionProbabilitiesForNode(const Node* node) const = 0;
};
