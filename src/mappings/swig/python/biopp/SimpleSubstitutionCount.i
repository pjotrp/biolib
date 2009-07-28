%module bpptest
%{
#include "SimpleSubstitutionCount.h"
using namespace bpp;
%}
%include "SubstitutionCount.i"
%include "Matrix.i"

class SimpleSubstitutionCount:public SubstitutionCount
{
  public:
    SimpleSubstitutionCount(const Alphabet * alphabet);
    virtual ~SimpleSubstitutionCount();

    double getNumberOfSubstitutions(int initialState, int finalState, double length) const;
    virtual Matrix<double> * getAllNumbersOfSubstitutions(double length) const;
    void setSubstitutionModel(const SubstitutionModel* model);
};
