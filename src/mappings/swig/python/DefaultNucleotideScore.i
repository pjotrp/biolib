%module bpptest
%{
#include "DefaultNucleotideScore.h"
using namespace bpp;
%}
%include "std_string.i"
using namespace std;
%include "AlphabetIndex2.i"
%include "NucleicAlphabet.i"
%include "AlphabetExceptions.i"
%include "Exceptions.i"
%include "Matrix.i"

class DefaultNucleotideScore: public AlphabetIndex2<double>
{
  public:
    DefaultNucleotideScore(const NucleicAlphabet * alphabet);
    virtual ~DefaultNucleotideScore();

    double getIndex(int state1, int state2) const throw (BadIntException);
    double getIndex(const string & state1, const string & state2) const throw (BadCharException);
    const Alphabet * getAlphabet() const;
    DefaultNucleotideScore * clone() const;
    Matrix<double> * getIndexMatrix() const;
};
