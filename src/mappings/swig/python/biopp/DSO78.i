%module bpptest
%{
#include "DSO78.h"
using namespace bpp;
%}
%include "ProteinSubstitutionModel.i"
%include "ProteicAlphabet.i"

class DSO78:public ProteinSubstitutionModel
{
  public:
    DSO78(const ProteicAlphabet * alpha);
    virtual ~DSO78();
    DSO78* clone() const;

    string getName() const;
};
