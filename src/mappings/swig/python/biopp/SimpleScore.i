%module bpptest
%{
#include "SimpleScore.h"
using namespace bpp;
%}
%include "std_string.i"
using namespace std;
%include "AlphabetIndex2.i"
%include "Alphabet.i"
%include "AlphabetExceptions.i"
%include "Exceptions.i"
%include "Matrix.i"

class SimpleScore:public AlphabetIndex2<double>
{
  public:
    SimpleScore(const Alphabet * alphabet, double match, double mismatch);
    virtual ~SimpleScore();
    SimpleScore * clone() const;

    double getIndex(int state1, int state2) const throw (BadIntException);
    double getIndex(const string & state1, const string & state2) const throw (BadCharException);
    const Alphabet * getAlphabet() const;
    Matrix<double> * getIndexMatrix() const;
};
