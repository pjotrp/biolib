%module bpptest
%{
#include "AlphabetIndex2.h"
using namespace bpp;
%}
%include "Alphabet.i"
%include "Clonable.i"
%include "Matrix.i"
%include "std_string.i"
using namespace std;

template <class T>
class AlphabetIndex2: public Clonable
{
  public:
    AlphabetIndex2();
    virtual ~AlphabetIndex2();

    virtual T getIndex(int state1, int state2) const = 0;
    virtual T getIndex(const string & state1, const string & state2) const = 0;
    virtual const Alphabet * getAlphabet() const = 0;
    virtual Matrix<T> * getIndexMatrix() const = 0;
};

%template(intAlphabetIndex2) AlphabetIndex2<int>;
%template(doubleAlphabetIndex2) AlphabetIndex2<double>;
