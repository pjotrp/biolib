%module bpptest
%{
#include "StandardCodonAlphabet.h"
using namespace bpp;
%}
%include "CodonAlphabet.i"

class StandardCodonAlphabet : public CodonAlphabet
{
  public:
    StandardCodonAlphabet(const NucleicAlphabet * alpha);
    virtual ~StandardCodonAlphabet();

    unsigned int getSize() const;
    unsigned int getNumberOfTypes() const;
    string getAlphabetType() const;
    bool isStop(int codon) const;
    bool isStop(const string & codon) const;
};
