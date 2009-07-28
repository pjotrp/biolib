%module bpptest
%{
#include "HomogeneousTreeLikelihood.h"
using namespace bpp;
%}
%include "TreeLikelihood.i"
%include "SubstitutionModel.i"

class HomogeneousTreeLikelihood :public virtual TreeLikelihood
{
  public:
    HomogeneousTreeLikelihood * clone() const = 0;

    virtual const SubstitutionModel * getSubstitutionModel() const = 0;
    virtual SubstitutionModel * getSubstitutionModel() = 0;
    virtual void setSubstitutionModel(SubstitutionModel * model) throw (Exception) = 0;
};
