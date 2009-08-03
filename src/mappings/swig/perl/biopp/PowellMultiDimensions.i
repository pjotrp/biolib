%module bpp_
%{
#include "PowellMultiDimensions.h"
using namespace bpp;
%}
%include "AbstractOptimizer.i"
//%include "VectorTools.i"
%include "DirectionFunction.i"

class PowellMultiDimensions:public AbstractOptimizer
{
	public:
		//class PMDStopCondition:public AbstractOptimizationStopCondition
		//{
		//	public:
		//		PMDStopCondition(PowellMultiDimensions * pmd):
		//		AbstractOptimizationStopCondition(pmd);
		//		virtual ~PMDStopCondition();
		//		PMDStopCondition* clone() const;

		//		void init();
		//		bool isToleranceReached() const;
		//};
		//friend class PMDStopCondition;

		PowellMultiDimensions(Function * function);
		virtual ~PowellMultiDimensions();

		PowellMultiDimensions* clone() const;

		double optimize() throw (Exception);
		void doInit(const ParameterList & params) throw (Exception);
		double doStep() throw (Exception);	
};
