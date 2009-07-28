%module bpptest
%{
#include "G2001.h"
using namespace bpp;
%}
%include "MarkovModulatedSubstitutionModel.i"
%include "DiscreteDistribution.i"
%include "Parameter.i"

%rename(__assign__) G2001::operator=;

class G2001:public MarkovModulatedSubstitutionModel
{
  public:
    G2001(ReversibleSubstitutionModel * model, DiscreteDistribution * rDist, double nu = 1., bool normalizeRateChanges = false);
    G2001(const G2001 & model): MarkovModulatedSubstitutionModel(model);
    G2001 & operator=(const G2001 & model);
    virtual ~G2001();
    G2001* clone() const;

    string getName() const;
    void fireParameterChanged(const ParameterList & parameters);
};
