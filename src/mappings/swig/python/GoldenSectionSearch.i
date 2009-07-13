%module bpp_
%{
#include "GoldenSectionSearch.h"
%}
%include "AbstractOptimizer.i"
namespace bpp
{
class GoldenSectionSearch:public AbstractOptimizer
{	
	public:
		class GSSStopCondition:public AbstractOptimizationStopCondition
		{
			public:
				GSSStopCondition(GoldenSectionSearch * gss):AbstractOptimizationStopCondition(gss);
				virtual ~GSSStopCondition();
        GSSStopCondition* clone() const;

				void init();
				bool isToleranceReached() const;
		};
	friend class GSSStopCondition;
	public:
		GoldenSectionSearch(Function * function);
		virtual ~GoldenSectionSearch();
    GoldenSectionSearch* clone() const;
	public:
		double getFunctionValue() const throw (NullPointerException);
    void doInit(const ParameterList & params) throw (Exception);
		double doStep() throw (Exception);
		void setInitialInterval(double inf, double sup);
    bool isInitialIntervalSet() const;
};
} 
