%module bpptest
%{
#include "AAChargeIndex.h"
using namespace bpp;
%}
%include "AlphabetIndex1.i"
%include "ProteicAlphabet.i"

class AAChargeIndex:public AlphabetIndex1<double>
{
  public:
    AAChargeIndex();
    virtual ~AAChargeIndex();
    AAChargeIndex * clone() const;

    double getIndex(int state) const throw (BadIntException);
    double getIndex(const string & state) const throw (BadCharException);
    vector<double> * getIndexVector() const;
    const Alphabet * getAlphabet() const;
};
