%module bpptest
%{
#include "AAIndex2Entry.h"
using namespace bpp;
%}
%include "AlphabetIndex2.i"
%include "ProteicAlphabet.i"
%include "Matrix.i"

%rename(__assign__) AAIndex2Entry::operator=;

class AAIndex2Entry: public AlphabetIndex2<double>
{
  public:
    AAIndex2Entry(istream & input, bool sym=true) throw (IOException);
    AAIndex2Entry(const AAIndex2Entry & index);
    AAIndex2Entry & operator=(const AAIndex2Entry & index);
    virtual ~AAIndex2Entry();

    const Alphabet * getAlphabet() const;
    AAIndex2Entry * clone() const;
    double getIndex(int state1, int state2) const throw (BadIntException);
    double getIndex(const string & state1, const string & state2) const throw (BadCharException);
    Matrix<double> * getIndexMatrix() const;
};
