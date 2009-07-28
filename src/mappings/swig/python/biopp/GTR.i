%module bpptest
%{
#include "GTR.h"
using namespace bpp;
%}
%include "NucleotideSubstitutionModel.i"
%include "Constraints.i"
%include "NucleicAlphabet.i"

class GTR:public NucleotideSubstitutionModel
{
  public:
    GTR(const NucleicAlphabet * alpha, double a = 1., double b = 1., double c = 1., double d = 1., double e = 1., double piA = 0.25, double piC = 0.25, double piG = 0.25, double piT = 0.25);
    virtual ~GTR();
    GTR* clone() const;

    string getName() const;
    void updateMatrices();
    void setFreqFromData(const SequenceContainer & data, unsigned int pseudoCount = 0);
};
