%module bpptest
%{
#include "BLOSUM50.h"
using namespace bpp;
%}
%include "std_string.i"
using namespace std;
%include "AlphabetIndex2.i"
%include "ProteicAlphabet.i"
%include "AlphabetExceptions.i"
%include "Exceptions.i"
%include "Matrix.i"

class BLOSUM50: public AlphabetIndex2<double>
{
  public:
    BLOSUM50();
    virtual ~BLOSUM50();
  public:
    double getIndex(int state1, int state2) const throw (BadIntException);
    double getIndex(const string & state1, const string & state2) const throw (BadCharException);
    const Alphabet * getAlphabet() const;
    BLOSUM50 * clone() const;
    Matrix<double> * getIndexMatrix() const;
};
