%module bpptest
%{
#include "JTT92.h"
using namespace bpp;
%}
%include "ProteinSubstitutionModel.i"
%include "ProteicAlphabet.i"

class JTT92:public ProteinSubstitutionModel
{
  public:
    JTT92(const ProteicAlphabet * alpha);
    virtual ~JTT92();
    JTT92 *clone() const;

    string getName() const;
};
