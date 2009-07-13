%module bpp_
%{
#include "ConstantDistribution.h"
%}
%include "AbstractDiscreteDistribution.i"
namespace bpp
{
class ConstantDistribution :public AbstractDiscreteDistribution
{
  public:
    ConstantDistribution(double value);
    virtual ~ConstantDistribution();
    ConstantDistribution * clone() const;

    Domain getDomain() const;
    void fireParameterChanged(const ParameterList & parameters);
    double randC() const throw (Exception);
};
} 
