%module bpptest
%{
#include "InvertebrateMitochondrialCodonAlphabet.h"
using namespace bpp;
%}
%include "CodonAlphabet.i"

class InvertebrateMitochondrialCodonAlphabet:public CodonAlphabet
{
  public:
    InvertebrateMitochondrialCodonAlphabet(const NucleicAlphabet * alpha);
    virtual ~InvertebrateMitochondrialCodonAlphabet();

    unsigned int getSize() const;
    unsigned int getNumberOfTypes() const;
    string getAlphabetType() const;
    bool isStop(      int      codon) const;
    bool isStop(const string & codon) const;
};
