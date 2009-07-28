%module bpptest
%{
#include "JCprotF.h"
using namespace bpp;
%}
%include "ProteicAlphabet.i"
%include "ProteinSubstitutionModelWithFrequencies.i"

class JCprotF:public ProteinSubstitutionModelWithFrequencies
{
  public:
    JCprotF(const ProteicAlphabet * alpha);
    virtual ~JCprotF();
    JCprotF* clone() const;

    string getName() const;
};
