%module bpp_
%{
#include "ConjugateGradientMultiDimensions.h"
using namespace bpp;
%}
%include "AbstractOptimizer.i"
%include "BrentOneDimension.i"
%include "DirectionFunction.i"

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

