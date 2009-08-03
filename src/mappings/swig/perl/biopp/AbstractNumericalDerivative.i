%module bpp_
%{
#include "AbstractNumericalDerivative.h"
using namespace bpp;
%}
%include "Functions.i"
%include "Matrix.i"
%include "std_map.i"
%include "std_vector.i"
%include "std_string.i"
using namespace std;

class AbstractNumericalDerivative:public DerivableSecondOrder,public FunctionWrapper
{
  public:
    AbstractNumericalDerivative (Function * function): FunctionWrapper(function), function1_(NULL), function2_(NULL), h_(0.0001), computeD1_(true), computeD2_(true), computeCrossD2_(false);
    AbstractNumericalDerivative (DerivableFirstOrder * function): FunctionWrapper(function), function1_(function), function2_(NULL), h_(0.0001), computeD1_(true), computeD2_(true), computeCrossD2_(false);
    AbstractNumericalDerivative (DerivableSecondOrder * function): FunctionWrapper(function), function1_(function), function2_(function), h_(0.0001), computeD1_(true), computeD2_(true), computeCrossD2_(false);
    virtual ~AbstractNumericalDerivative();
    AbstractNumericalDerivative* clone() const = 0;

    void setInterval(double h);
    void setParametersToDerivate(const vector<string> & variables);
    void enableFirstOrderDerivatives(bool yn);
    bool enableFirstOrderDerivatives() const;
    double getFirstOrderDerivative(const string & variable) const throw (Exception);
    void enableSecondOrderDerivatives(bool yn);
    bool enableSecondOrderDerivatives() const;
    double getSecondOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable1, const string & variable2) const throw (Exception);
    double f(const ParameterList & parameters) throw (Exception);
    void setParameters(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    void setAllParametersValues(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    void setParameterValue(const string & name, double value) throw (ParameterNotFoundException, ConstraintException);
    void setParametersValues(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    void matchParametersValues(const ParameterList & parameters) throw (ConstraintException);
    void enableSecondOrderCrossDerivatives(bool yn);
    bool enableSecondOrderCrossDerivatives() const;
};
