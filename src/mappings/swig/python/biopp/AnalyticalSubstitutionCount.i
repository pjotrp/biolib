%module bpptest
%{
#include "AnalyticalSubstitutionCount.h"
using namespace bpp;
%}
%include "SubstitutionCount.i"
%include "SubstitutionModel.i"

class AnalyticalSubstitutionCount:public SubstitutionCount
{
  public:
    AnalyticalSubstitutionCount(const SubstitutionModel * model, int cutOff);
    virtual ~AnalyticalSubstitutionCount();

    double getNumberOfSubstitutions(int initialState, int finalState, double length) const;
    Matrix<double> * getAllNumbersOfSubstitutions(double length) const;
    void setSubstitutionModel(const SubstitutionModel* model);
};
