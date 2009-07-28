%module bpptest
%{
#include "NucleotideSubstitutionModel.h"
using namespace bpp;
%}
%include "AbstractSubstitutionModel.i"
%include "NucleicAlphabet.i"

class NucleotideSubstitutionModel :public AbstractReversibleSubstitutionModel
{
  public:
    NucleotideSubstitutionModel(const NucleicAlphabet * alpha, const string& prefix);
    virtual ~NucleotideSubstitutionModel();
    NucleotideSubstitutionModel* clone() const = 0;

    virtual unsigned int getNumberOfStates() const;
};
