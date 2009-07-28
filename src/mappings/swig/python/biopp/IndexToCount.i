%module bpptest
%{
#include "IndexToCount.h"
using namespace bpp;
%}
%include "SubstitutionCount.i"
%include "Alphabet.i"
%include "AlphabetIndex2.i"

class IndexToCount:public SubstitutionCount
{
  public:
    IndexToCount(const AlphabetIndex2<double> * ai2, bool deleteDistance);
    virtual ~IndexToCount();
    double getNumberOfSubstitutions(int initialState, int finalState, double length) const;
    Matrix<double> * getAllNumbersOfSubstitutions(double length) const;
    void setSubstitutionModel(const SubstitutionModel* model);
    const AlphabetIndex2<double> * getAlphabetIndex2() const;
};
