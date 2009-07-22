%module bpp_
%{
#include "InvariantMixedDiscreteDistribution.h"
using namespace bpp;
%}
%include "AbstractDiscreteDistribution.i"

class InvariantMixedDiscreteDistribution:public AbstractDiscreteDistribution
{
  public:
    InvariantMixedDiscreteDistribution(
        DiscreteDistribution* dist, double p, double invariant = 0., const string& parameterPrefix = "");
    virtual ~InvariantMixedDiscreteDistribution();
    InvariantMixedDiscreteDistribution(const InvariantMixedDiscreteDistribution& imdd):
      AbstractDiscreteDistribution(imdd);
    InvariantMixedDiscreteDistribution& operator=(const InvariantMixedDiscreteDistribution& imdd);
    InvariantMixedDiscreteDistribution* clone() const;

    Domain getDomain() const;
		void fireParameterChanged(const ParameterList & parameters);
    void setNamespace(const string& prefix);
    const DiscreteDistribution * getVariableSubDistribution() const;
};
