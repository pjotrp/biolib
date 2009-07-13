%module bpp_
%{
#include "SimpleNewtonMultiDimensions.h"
%}
%include "AbstractOptimizer.i"
%include "NewtonOneDimension.i"
namespace bpp
{
class SimpleNewtonMultiDimensions:
  public AbstractOptimizer
{
	public:
		SimpleNewtonMultiDimensions(DerivableSecondOrder * function);
    SimpleNewtonMultiDimensions(const SimpleNewtonMultiDimensions & opt);
    SimpleNewtonMultiDimensions & operator=(const SimpleNewtonMultiDimensions & opt);
		virtual ~SimpleNewtonMultiDimensions();
    SimpleNewtonMultiDimensions* clone() const;

		void setFunction(Function * function);
		void doInit(const ParameterList & params) throw (Exception);
		double doStep() throw (Exception);
    Optimizer * getOneDimensionOptimizer(); 
    const Optimizer * getOneDimensionOptimizer() const; 
};
} 
