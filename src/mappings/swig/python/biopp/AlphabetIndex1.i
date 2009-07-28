%module bpptest
%{
#include "AlphabetIndex1.h"
using namespace bpp;
%}
%include "Alphabet.i"
%include "Clonable.i"
%include "std_string.i"

template <class T>
class AlphabetIndex1: public Clonable
{
  public:
    AlphabetIndex1();
    virtual ~AlphabetIndex1();

    virtual T getIndex(int state) const = 0;
    virtual T getIndex(const string & state) const = 0;
    virtual const Alphabet * getAlphabet() const = 0;
    virtual vector<T> * getIndexVector() const = 0;
};

%template(intAlphabetIndex1) AlphabetIndex1<int>;
%template(doubleAlphabetIndex1) AlphabetIndex1<double>;