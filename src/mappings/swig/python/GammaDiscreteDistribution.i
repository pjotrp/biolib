%module bpp_
%{
#include "GammaDiscreteDistribution.h"
using namespace bpp;
%}
%include "AbstractDiscreteDistribution.i"
%include "Constraints.i"
%include "RandomTools.i"

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
