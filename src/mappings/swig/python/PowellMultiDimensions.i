%module bpp_
%{
#include "PowellMultiDimensions.h"
%}
%include "AbstractOptimizer.i"
%include "VectorTools.i"
%include "DirectionFunction.i"
namespace bpp
{
class PowellMultiDimensions:
  public AbstractOptimizer
{
	public:
		class PMDStopCondition:
      public AbstractOptimizationStopCondition
		{
			public:
				PMDStopCondition(PowellMultiDimensions * pmd):
          AbstractOptimizationStopCondition(pmd);
				virtual ~PMDStopCondition();
        PMDStopCondition* clone() const;
			public:
				void init();
				bool isToleranceReached() const;
		};
	friend class PMDStopCondition;

		PowellMultiDimensions(Function * function);
		virtual ~PowellMultiDimensions();

    PowellMultiDimensions* clone() const;

		double optimize() throw (Exception);
		void doInit(const ParameterList & params) throw (Exception);
    double doStep() throw (Exception);	
};
} 
