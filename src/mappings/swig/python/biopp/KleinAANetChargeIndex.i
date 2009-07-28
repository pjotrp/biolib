%module bpptest
%{
#include "KleinAANetChargeIndex.h"
using namespace bpp;
%}
%include "AlphabetIndex1.i"
%include "ProteicAlphabet.i"

class KleinAANetChargeIndex:public AlphabetIndex1<double>
{
  public:
    KleinAANetChargeIndex();
    virtual ~KleinAANetChargeIndex();
    KleinAANetChargeIndex * clone() const;

    double getIndex(int state) const throw (BadIntException);
    double getIndex(const string & state) const throw (BadCharException);
    vector<double> * getIndexVector() const;
    const Alphabet * getAlphabet() const;
};
