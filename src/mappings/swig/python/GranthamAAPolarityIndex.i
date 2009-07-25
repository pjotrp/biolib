%module bpptest
%{
#include "GranthamAAPolarityIndex.h"
using namespace bpp;
%}
%include "AlphabetIndex1.i"
%include "ProteicAlphabet.i"

class GranthamAAPolarityIndex:public AlphabetIndex1<double>
{
  public:
    GranthamAAPolarityIndex()
    virtual ~GranthamAAPolarityIndex();
    GranthamAAPolarityIndex * clone() const;

    double getIndex(int state) const throw (BadIntException);
    double getIndex(const string & state) const throw (BadCharException);
    vector<double> * getIndexVector() const;
    const Alphabet * getAlphabet() const;
};
