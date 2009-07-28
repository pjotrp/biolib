%module bpptest
%{
#include "NonHomogeneousTreeLikelihood.h"
using namespace bpp;
%}
%include "TreeLikelihood.i"
%include "SubstitutionModelSet.i"

class NonHomogeneousTreeLikelihood :public virtual TreeLikelihood
{
  public:
    NonHomogeneousTreeLikelihood * clone() const = 0;

    virtual const SubstitutionModelSet * getSubstitutionModelSet() const = 0;
    virtual SubstitutionModelSet * getSubstitutionModelSet() = 0;
    virtual void setSubstitutionModelSet(SubstitutionModelSet * model) throw (Exception) = 0;
    virtual ParameterList getRootFrequenciesParameters() const = 0;
};
