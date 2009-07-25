%module bpptest
%{
#include "GranthamAAVolumeIndex.h"
using namespace bpp;
%}
%include "AlphabetIndex1.i"
%include "ProteicAlphabet.i"

class GranthamAAVolumeIndex:public AlphabetIndex1<double>
{
  public:
    GranthamAAVolumeIndex();
    virtual ~GranthamAAVolumeIndex();
    GranthamAAVolumeIndex * clone() const;

    double getIndex(int state) const throw (BadIntException);
    double getIndex(const string & state) const throw (BadCharException);
    vector<double> * getIndexVector() const;
    const Alphabet * getAlphabet() const;
};
