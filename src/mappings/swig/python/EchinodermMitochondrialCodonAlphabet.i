%module bpptest
%{
#include "EchinodermMitochondrialCodonAlphabet.h"
using namespace bpp;
%}
%include "CodonAlphabet.i"

class EchinodermMitochondrialCodonAlphabet : public CodonAlphabet
{
  public:
    EchinodermMitochondrialCodonAlphabet(const NucleicAlphabet * alpha);
    virtual ~EchinodermMitochondrialCodonAlphabet();

    unsigned int getSize() const;
    unsigned int getNumberOfTypes() const;
    string getAlphabetType() const;
    bool isStop(      int      codon) const;
    bool isStop(const string & codon) const;
};
