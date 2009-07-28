%module bpptest
%{
#include "SubstitutionCount.h"
using namespace bpp;
%}
%include "SubstitutionModel.i"
%include "Matrix.i"

class SubstitutionCount
{
  public:
    SubstitutionCount();
    virtual ~SubstitutionCount();

    virtual double getNumberOfSubstitutions(int initialState, int finalState, double length) const = 0;
    virtual Matrix<double> * getAllNumbersOfSubstitutions(double length) const = 0;
    virtual void setSubstitutionModel(const SubstitutionModel* model) = 0;
};
