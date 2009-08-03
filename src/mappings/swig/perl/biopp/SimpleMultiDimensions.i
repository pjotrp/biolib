%module bpp_
%{
#include "SimpleMultiDimensions.h"
using namespace bpp;
%}
%include "AbstractOptimizer.i"
%include "BrentOneDimension.i"

%ignore SimpleMultiDimensions::operator=;

class SimpleMultiDimensions:public AbstractOptimizer
{
	public:
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
