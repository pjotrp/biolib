%module bpp_
%{
#include "BrentOneDimension.h"
using namespace bpp;
%}
%include "AbstractOptimizer.i"

class BrentOneDimension:public AbstractOptimizer
{
	public:
		class BODStopCondition:public AbstractOptimizationStopCondition
		{
      public:
				BODStopCondition(BrentOneDimension * bod):AbstractOptimizationStopCondition(bod);
				virtual ~BODStopCondition();
        BODStopCondition* clone() const; 

				void init();
				bool isToleranceReached() const;
		};

	friend class BODStopCondition;

	public:
		BrentOneDimension(Function * function = NULL);
		virtual ~BrentOneDimension();
    BrentOneDimension* clone() const;

    double optimize() throw (Exception); 
    void doInit(const ParameterList & params) throw (Exception);
    double doStep() throw (Exception);
		void setInitialInterval(double inf, double sup);
    bool isInitialIntervalSet() const;
	static double CGOLD;
	static double ZEPS;
};
