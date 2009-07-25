%module bpptest
%{
#include "NucleicAlphabet.h"
using namespace bpp;
%}

%include "AbstractAlphabet.i"

class NucleicAlphabet :public AbstractAlphabet
{
  public:
    NucleicAlphabet();
    virtual ~NucleicAlphabet();

    unsigned int getSize() const;
    unsigned int getNumberOfTypes() const;
    int getUnknownCharacterCode() const;
    bool isUnresolved(int state) const;
    bool isUnresolved(const string & state) const;    
};
