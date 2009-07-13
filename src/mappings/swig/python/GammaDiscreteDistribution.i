%module bpp_
%{
#include "GammaDiscreteDistribution.h"
%}
%include "AbstractDiscreteDistribution.i"
%include "Constraints.i"
%include "RandomTools.i"
namespace bpp
{
class GammaDiscreteDistribution:public AbstractDiscreteDistribution
{
	public:
		GammaDiscreteDistribution(unsigned int n, double alpha = 1., double beta= 1., const string& parameterPrefix="");
		virtual ~GammaDiscreteDistribution();
    GammaDiscreteDistribution * clone() const;

    Domain getDomain() const;
		void fireParameterChanged(const ParameterList & parameters);
    double randC() const throw (Exception);
};
} 
