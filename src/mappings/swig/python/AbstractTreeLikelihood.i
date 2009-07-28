%module bpptest
%{
#include "AbstractTreeLikelihood.h"
using namespace bpp;
%}
%include "TreeLikelihood.i"
%include "Tree.i"
%include "TreeTemplate.i"
%include "AbstractParametrizable.i"
%include "SiteContainer.i"

%rename(__assign__) AbstractTreeLikelihood::operator=;

class AbstractTreeLikelihood :public virtual TreeLikelihood,public AbstractParametrizable
{
  protected:
    const SiteContainer * _data;
    mutable TreeTemplate<Node> * _tree;
    bool _computeFirstOrderDerivatives;
    bool _computeSecondOrderDerivatives;
    bool _initialized;

    AbstractTreeLikelihood();
    AbstractTreeLikelihood(const AbstractTreeLikelihood & lik);
    AbstractTreeLikelihood & operator=(const AbstractTreeLikelihood & lik);
    virtual ~AbstractTreeLikelihood();

    const SiteContainer * getData() const;
    const Alphabet * getAlphabet() const;  
    Vdouble getLikelihoodForEachSite() const;
    Vdouble getLogLikelihoodForEachSite() const;
    VVdouble getLikelihoodForEachSiteForEachState() const;
    VVdouble getLogLikelihoodForEachSiteForEachState() const;
    unsigned int getNumberOfSites() const;
    unsigned int getNumberOfStates() const;
    const Tree * getTree() const;
    void enableDerivatives(bool yn);
    void enableFirstOrderDerivatives(bool yn);
    void enableSecondOrderDerivatives(bool yn);
    bool enableFirstOrderDerivatives() const;
    bool enableSecondOrderDerivatives() const;
    bool isInitialized() const;
    void initialize() throw (Exception);
};
