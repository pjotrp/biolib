%module bpptest
%{
#include "JTT92F.h"
using namespace bpp;
%}
%include "ProteinSubstitutionModelWithFrequencies.i"
%include "ProteicAlphabet.i"


class JTT92F:public ProteinSubstitutionModelWithFrequencies
{
  public:
    JTT92F(const ProteicAlphabet * alpha);
    virtual ~JTT92F();
    JTT92F* clone() const;

    string getName() const;
};
