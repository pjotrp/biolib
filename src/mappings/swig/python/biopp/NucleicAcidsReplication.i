%module bpptest
%{
#include "NucleicAcidsReplication.h"
using namespace bpp;
%}
%include "Translator.i"
%include "NucleicAlphabet.i"
%include "std_map.i"
using namespace std;

class NucleicAcidsReplication : public ReverseTranslator
{
  public:
    NucleicAcidsReplication(const NucleicAlphabet * nuc1, const NucleicAlphabet * nuc2);
    virtual ~NucleicAcidsReplication();

    const Alphabet * getSourceAlphabet() const;
    const Alphabet * getTargetAlphabet() const;
    int translate(int state) const throw (BadIntException);
    string translate(const string & state) const throw (BadCharException);
    Sequence * translate(const Sequence & sequence) const throw (AlphabetMismatchException);
    int reverse(int state) const throw (BadIntException);
    string reverse(const string & state) const throw (BadCharException);
    Sequence * reverse(const Sequence & sequence) const throw (AlphabetMismatchException, Exception);
};
