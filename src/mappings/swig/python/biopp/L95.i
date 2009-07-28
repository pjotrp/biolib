%module bpptest
%{
#include "L95.h"
using namespace bpp;
%}
%include "NucleotideSubstitutionModel.i"
%include "Constraints.i"
%include "NucleicAlphabet.i"

class L95:public NucleotideSubstitutionModel
{
  public:
    L95(const NucleicAlphabet * alpha,double beta = 1.,double gamma = 1.,double delta = 1.,double theta = 0.5);
    virtual ~L95();
    L95* clone() const;

    string getName() const;
    void updateMatrices();
    void setFreqFromData(const SequenceContainer & data);
};
