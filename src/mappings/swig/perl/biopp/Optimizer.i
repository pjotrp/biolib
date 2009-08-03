%module bpp_
%{
#include "Optimizer.h"
using namespace bpp;
%}
%include "Functions.i"
%include "ParameterList.i"
%include "OptimizationStopCondition.i"
%include "Clonable.i"
//%include "std_iostream.i"
using namespace std;

class OptimizationEvent
{
  public:
    OptimizationEvent(Optimizer * optimizer): _optimizer(optimizer);
    virtual ~OptimizationEvent();

    Optimizer * getOptimizer();
    const Optimizer * getOptimizer() const;
};

class OptimizationListener
{
  public:
    OptimizationListener();
    virtual ~OptimizationListener();

    virtual void optimizationInitializationPerformed(const OptimizationEvent & event) = 0;
    virtual void optimizationStepPerformed(const OptimizationEvent & event) = 0;
    virtual bool listenerModifiesParameters() const = 0;
};

class Optimizer:public virtual Clonable
{
  public:
    Optimizer();
    virtual ~Optimizer();
    Optimizer * clone() const = 0;

    virtual void init(const ParameterList & params) throw (Exception) = 0;
    virtual bool isInitialized() const = 0;
    virtual double step() throw (Exception) = 0;
    virtual ParameterList getParameters() const = 0;
    virtual double getFunctionValue() const throw (NullPointerException) = 0;
    virtual double optimize() throw (Exception) = 0;
    virtual void setFunction(Function * function) = 0;
    virtual const Function * getFunction() const = 0;
    virtual Function * getFunction() = 0;
    virtual void setMessageHandler(ostream * mh) = 0;
    virtual void setProfiler(ostream * profiler) = 0;
    virtual  int getNumberOfEvaluations() const = 0;
    virtual void setStopCondition(const OptimizationStopCondition & stopCondition) = 0;
    virtual OptimizationStopCondition * getStopCondition() = 0;
    virtual const OptimizationStopCondition * getStopCondition() const = 0;
    virtual OptimizationStopCondition * getDefaultStopCondition() = 0;
    virtual const OptimizationStopCondition * getDefaultStopCondition() const = 0;
    virtual bool isToleranceReached() const = 0;
    virtual bool isMaximumNumberOfEvaluationsReached() const = 0;
    virtual void setMaximumNumberOfEvaluations(unsigned int max) = 0;
    virtual void setVerbose(unsigned int v) = 0;
    virtual unsigned int getVerbose() const = 0;
    virtual void setConstraintPolicy(const string & constraintPolicy) = 0;
    virtual string getConstraintPolicy() const = 0;
    virtual void addOptimizationListener(OptimizationListener * listener) = 0; 
};

