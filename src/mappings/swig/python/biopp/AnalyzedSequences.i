%module bpptest
%{
#include "AnalyzedSequences.h"
using namespace bpp;
%}
%include "Alphabet.i"
%include "DNA.i"
%include "RNA.i"
%include "ProteicAlphabet.i"

class AnalyzedSequences
{
  public: 
    AnalyzedSequences();
    ~AnalyzedSequences();

    void setAlphabet(const Alphabet * alpha);
    void setAlphabet(const string & alpha_type) throw (Exception);
    const Alphabet * getAlphabet() const;
    string getAlphabetType() const;
};
