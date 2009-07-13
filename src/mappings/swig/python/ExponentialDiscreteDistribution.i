%module bpp_
%{
#include "ExponentialDiscreteDistribution.h"
%}
%include "AbstractDiscreteDistribution.i"
%include "Constraints.i"
%include "RandomTools.i"
namespace bpp
{
class ExponentialDiscreteDistribution:public AbstractDiscreteDistribution
{
	public:
		ExponentialDiscreteDistribution(unsigned int n, double lambda = 1., bool median=false, const string& parameterPrefix="");
    ExponentialDiscreteDistribution(const ExponentialDiscreteDistribution & dist):AbstractDiscreteDistribution(dist),bounds_(dist.bounds_),lambdaConstraint_(dynamic_cast<IncludingPositiveReal *>(dist.lambdaConstraint_->clone())),median_(dist.median_);
    ExponentialDiscreteDistribution & operator=(const ExponentialDiscreteDistribution & dist);
    ExponentialDiscreteDistribution* clone() const;

    Domain getDomain() const;
		void fireParameterChanged(const ParameterList & parameters);

    double randC() const throw (Exception);
};
} 
