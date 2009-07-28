%module bpptest
%{
#include "TS98.h"
using namespace bpp;
%}
%include "MarkovModulatedSubstitutionModel.i"
%include "DiscreteDistribution.i"
%include "Parameter.i"

class TS98:public MarkovModulatedSubstitutionModel
{
  public:
    TS98(ReversibleSubstitutionModel * model, double s1 = 1., double s2 = 1., bool normalizeRateChanges = false):MarkovModulatedSubstitutionModel(model, normalizeRateChanges, "TS98.");
    virtual ~TS98();
    TS98* clone() const;

    string getName() const;
};
