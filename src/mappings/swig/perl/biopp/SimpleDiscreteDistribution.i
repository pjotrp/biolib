%module bpp_
%{
#include "SimpleDiscreteDistribution.h"
using namespace bpp;
%}
%include "AbstractDiscreteDistribution.i"
%include "std_map.i"
using namespace std;
class SimpleDiscreteDistribution:public AbstractDiscreteDistribution
{
  public:
    SimpleDiscreteDistribution(const map<double, double> & distribution);
    virtual ~SimpleDiscreteDistribution();
    SimpleDiscreteDistribution * clone() const;

    void fireParameterChanged(const ParameterList & parameters);
    Domain getDomain() const;
};
