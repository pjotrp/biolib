%module bpp_
%{
#include "OptimizationStopCondition.h"
using namespace bpp;
%}
%include "ParameterList.i"

class Optimizer;
class OptimizationStopCondition:public virtual Clonable
{
	public:
		OptimizationStopCondition();
		virtual ~OptimizationStopCondition();
    OptimizationStopCondition * clone() const = 0;

    virtual const Optimizer * getOptimizer() const = 0;
    virtual void setOptimizer(const Optimizer * optimizer) = 0;
		virtual void init() = 0;
		virtual bool isToleranceReached() const = 0;
		virtual void setTolerance(double tolerance) = 0;
		virtual double getTolerance() const = 0;
};

class AbstractOptimizationStopCondition:public virtual OptimizationStopCondition
{
	public:
		AbstractOptimizationStopCondition(const Optimizer * optimizer);
		AbstractOptimizationStopCondition(const Optimizer * optimizer, double tolerance);
		AbstractOptimizationStopCondition(const Optimizer * optimizer, int burnin);
		AbstractOptimizationStopCondition(const Optimizer * optimizer, double tolerance, int burnin);
		virtual ~AbstractOptimizationStopCondition();

    const Optimizer * getOptimizer() const;
    void setOptimizer(const Optimizer * optimizer);
		void setTolerance(double tolerance);
		double getTolerance() const;
		virtual void resetCounter();
		virtual void setBurnin(int burnin);
		virtual int getBurnin() const;
};

class ParametersStopCondition:
  public AbstractOptimizationStopCondition
{
	public:
		ParametersStopCondition(const Optimizer * optimizer);
		ParametersStopCondition(const Optimizer * optimizer, double tolerance);
		ParametersStopCondition(const Optimizer * optimizer, int burnin);
		ParametersStopCondition(const Optimizer * optimizer, double tolerance, int burnin);
		virtual ~ParametersStopCondition();
    ParametersStopCondition* clone() const;

		void init();
		bool isToleranceReached() const;
};

class FunctionStopCondition:
  public AbstractOptimizationStopCondition
{
	public:
		FunctionStopCondition(const Optimizer * optimizer);
		FunctionStopCondition(const Optimizer * optimizer, double tolerance);
		FunctionStopCondition(const Optimizer * optimizer, int burnin);
		FunctionStopCondition(const Optimizer * optimizer, double tolerance, int burnin);
		virtual ~FunctionStopCondition();
    FunctionStopCondition* clone() const;

		void init();
		bool isToleranceReached() const;
};
