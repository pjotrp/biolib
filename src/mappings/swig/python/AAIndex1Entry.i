%module bpptest
%{
#include "AAIndex1Entry.h"
using namespace bpp;
%}
%include "AlphabetIndex1.i"
%include "ProteicAlphabet.i"

%rename(__assign__) AAIndex1Entry::operator=;

class AAIndex1Entry:public AlphabetIndex1<double>
{
  public:
    AAIndex1Entry(istream & input) throw (IOException);
    AAIndex1Entry(const AAIndex1Entry & index);
    AAIndex1Entry & operator=(const AAIndex1Entry & index);
    virtual ~AAIndex1Entry();
    AAIndex1Entry * clone() const;

    double getIndex(int state) const throw (BadIntException);
    double getIndex(const string & state) const throw (BadCharException);
    vector<double> * getIndexVector() const;
    const Alphabet * getAlphabet() const;
};
