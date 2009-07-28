%module bpptest
%{
#include "DSO78F.h"
using namespace bpp;
%}
%include "ProteinSubstitutionModelWithFrequencies.i"
%include "ProteicAlphabet.i"

class DSO78F:public ProteinSubstitutionModelWithFrequencies
{
  public:
    DSO78F(const ProteicAlphabet * alpha);
    virtual ~DSO78F();
    DSO78F* clone() const;

    string getName() const;
};
