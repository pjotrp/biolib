%module bpptest
%{
#include "NumTools.h"
#include "SimpleIndexDistance.h"
using namespace bpp;
%}
%include "std_string.i"
using namespace std;
%include "AlphabetIndex1.i"
%include "AlphabetIndex2.i"
%include "ProteicAlphabet.i"
%include "AlphabetExceptions.i"
%include "Exceptions.i"
%include "Matrix.i"

template<class T>
class SimpleIndexDistance:public AlphabetIndex2<T>
{
  public:
    SimpleIndexDistance(const AlphabetIndex1<T> & index);
    virtual ~SimpleIndexDistance();

    T getIndex(int state1, int state2) const throw (BadIntException);
    T getIndex(const string & state1, const string & state2) const throw (BadCharException);
    const Alphabet * getAlphabet() const;
    Clonable * clone() const;
    Matrix<T> * getIndexMatrix() const;

    void setSymmetric(bool yn);
    bool isSymmetric() const;
    const AlphabetIndex1<T> * getAlphabetIndex1() const;
    AlphabetIndex1<T> * getAlphabetIndex1();
};

%template(intSimpleIndexDistance) SimpleIndexDistance<int>;
%template(doubleSimpleIndexDistance) SimpleIndexDistance<double>;
