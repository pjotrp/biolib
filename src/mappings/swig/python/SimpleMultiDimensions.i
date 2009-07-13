%module bpp_
%{
#include "SimpleMultiDimensions.h"
%}
%include "AbstractOptimizer.i"
%include "BrentOneDimension.i"
namespace bpp
{
class SimpleMultiDimensions:
  public AbstractOptimizer
{
		SimpleMultiDimensions(Function * function);
    SimpleMultiDimensions(const SimpleMultiDimensions & opt);
    SimpleMultiDimensions & operator=(const SimpleMultiDimensions & opt);
		virtual ~SimpleMultiDimensions();
    SimpleMultiDimensions* clone() const;

		void setFunction(Function * function);
		void doInit(const ParameterList & params) throw (Exception);
    double doStep() throw (Exception);
    Optimizer * getOneDimensionOptimizer(); 
    const Optimizer * getOneDimensionOptimizer() const; 
};
} 
