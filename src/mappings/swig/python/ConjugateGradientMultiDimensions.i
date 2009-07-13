%module bpp_
%{
#include "ConjugateGradientMultiDimensions.h"
%}
%include "AbstractOptimizer.i"
%include "BrentOneDimension.i"
%include "DirectionFunction.i"
namespace bpp
{
class ConjugateGradientMultiDimensions:public AbstractOptimizer
{
  public:
    ConjugateGradientMultiDimensions(DerivableFirstOrder * function);
    virtual ~ConjugateGradientMultiDimensions();
    ConjugateGradientMultiDimensions* clone() const;

		void doInit(const ParameterList & params) throw (Exception);
		double doStep() throw (Exception);
    void getGradient(vector<double> & gradient) const;
};
} 
