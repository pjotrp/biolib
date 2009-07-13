%module bpp_
%{
#include "AbstractOptimizer.h"
%}
%include "Optimizer.i"
namespace bpp
{
class AbstractOptimizer:public Optimizer
{
  public:
    AbstractOptimizer(Function * function = NULL);
    AbstractOptimizer(const AbstractOptimizer & opt);
    AbstractOptimizer & operator=(const AbstractOptimizer & opt);
    virtual ~AbstractOptimizer();

    void init(const ParameterList & params) throw (Exception);
    double step() throw (Exception);
    double optimize() throw (Exception);
    bool isInitialized() const;
    ParameterList getParameters() const;
    void setFunction(Function * function);
    const Function * getFunction() const;
    Function * getFunction();
    double getFunctionValue() const throw (NullPointerException);
    void setMessageHandler(ostream * mh);
    void setProfiler(ostream * profiler);
    int getNumberOfEvaluations() const;
    void setStopCondition(const OptimizationStopCondition & stopCondition);
    OptimizationStopCondition * getStopCondition();
    const OptimizationStopCondition * getStopCondition() const;
    OptimizationStopCondition * getDefaultStopCondition();
    const OptimizationStopCondition * getDefaultStopCondition() const;
    bool isToleranceReached() const;
    bool isMaximumNumberOfEvaluationsReached() const;
    void setMaximumNumberOfEvaluations(unsigned int max);
    void setVerbose(unsigned int v);
    unsigned int getVerbose() const;
    void setConstraintPolicy(const string & constraintPolicy);
    string getConstraintPolicy() const;
    void addOptimizationListener(OptimizationListener * listener);
    void updateParameters(bool yn);
    bool updateParameters() const;
    void setOptimizationProgressCharacter(const string & c);
    string getOptimizationProgressCharacter() const;
};
} 
