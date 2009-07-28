%module bpptest
%{
#include "ProteinSubstitutionModel.h"
using namespace bpp;
%}
%include "AbstractSubstitutionModel.i"
%include "ProteicAlphabet.i"

class ProteinSubstitutionModel:public AbstractReversibleSubstitutionModel
{
  public:
    ProteinSubstitutionModel(const ProteicAlphabet * alpha, const string& prefix);
    virtual ~ProteinSubstitutionModel();
    ProteinSubstitutionModel* clone() const = 0;

    unsigned int getNumberOfStates() const;
};
