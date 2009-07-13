%module bpp_
%{
#include "Functions.h"
%}
%include "ParameterList.i"
%include "Parametrizable.i"
%include "ParameterExceptions.i"
%include "Clonable.i"
//#include <cmath>
using namespace std;
namespace bpp
{
class Function:public virtual Parametrizable
{    
  public:
    Function();
    virtual ~Function();

    virtual void setParameters(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException, Exception) = 0;
    virtual double getValue() const throw (Exception) = 0;
    virtual double f(const ParameterList & parameters) throw (Exception);
};
class DerivableFirstOrder:public virtual Function
{
  public:
    DerivableFirstOrder();
    virtual ~DerivableFirstOrder();
    DerivableFirstOrder * clone() const = 0;

    virtual void enableFirstOrderDerivatives(bool yn) = 0;
    virtual bool enableFirstOrderDerivatives() const = 0;
    virtual double getFirstOrderDerivative(const string & variable) const throw (Exception) = 0;
    virtual double df(const string & variable, const ParameterList & parameters) throw (Exception);
};

class DerivableSecondOrder:public virtual DerivableFirstOrder
{
  public:
    DerivableSecondOrder();
    virtual ~DerivableSecondOrder();
    DerivableSecondOrder * clone() const = 0;

    virtual void enableSecondOrderDerivatives(bool yn) = 0;
    virtual bool enableSecondOrderDerivatives() const = 0;
    virtual double getSecondOrderDerivative(const string & variable) const throw (Exception) = 0;
    virtual double d2f(const string & variable, const ParameterList & parameters) throw (Exception);
    virtual double getSecondOrderDerivative(const string & variable1, const string & variable2) const throw (Exception) = 0;  
    virtual double d2f(const string & variable1, const string & variable2, const ParameterList & parameters) throw (Exception);
};

class FunctionWrapper:public virtual Function
{
  public:
    FunctionWrapper(Function * function): function_(function);

    bool hasParameter(const string& name) const;
    void setParameters(const ParameterList & parameters)throw (ParameterNotFoundException, ConstraintException);
    const ParameterList & getParameters() const throw (Exception);
    const Parameter & getParameter(const string & name) const throw (ParameterNotFoundException);
    double getValue() const throw (Exception);
    double f(const ParameterList & parameters) throw (Exception);
    double getParameterValue(const string & name) const throw (ParameterNotFoundException);
    void setAllParametersValues(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    void setParameterValue(const string & name, double value) throw (ParameterNotFoundException, ConstraintException);
    void setParametersValues(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    void matchParametersValues(const ParameterList & parameters) throw (ConstraintException);
    unsigned int getNumberOfParameters() const;
    void setNamespace(const string& prefix);
    string getNamespace() const;
    string getParameterNameWithoutNamespace(const string& name) const;
};

class InfinityFunctionWrapper:public FunctionWrapper
{
  public:
    InfinityFunctionWrapper(Function * function):FunctionWrapper(function),constraintMatch_(false);
    virtual ~InfinityFunctionWrapper();
    InfinityFunctionWrapper * clone() const;

    void setParameters(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    double getValue() const throw (Exception);
    double f(const ParameterList& parameters) throw (Exception);
    void setAllParametersValues(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    void setParameterValue(const string & name, double value) throw (ParameterNotFoundException, ConstraintException);
    void setParametersValues(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    void matchParametersValues(const ParameterList & parameters) throw (ConstraintException);
};

class InfinityDerivableFirstOrderWrapper:public virtual InfinityFunctionWrapper
{
  public:
    InfinityDerivableFirstOrderWrapper(DerivableFirstOrder * function): InfinityFunctionWrapper(function);
    virtual ~InfinityDerivableFirstOrderWrapper();
    InfinityDerivableFirstOrderWrapper * clone() const;

    double getFirstOrderDerivative(const string & variable) const throw (Exception);
    double df(const string & variable, const ParameterList & parameters) throw (Exception);
};

class InfinityDerivableSecondOrderWrapper:public virtual InfinityDerivableFirstOrderWrapper
{
  public:
    InfinityDerivableSecondOrderWrapper(DerivableFirstOrder * function):InfinityFunctionWrapper(function),InfinityDerivableFirstOrderWrapper(function);
    virtual ~InfinityDerivableSecondOrderWrapper();
    InfinityDerivableSecondOrderWrapper * clone() const;

    double getSecondOrderDerivative(const string & variable) const throw (Exception);
    double d2f(const string & variable, const ParameterList & parameters) throw (Exception);
    double getSecondOrderDerivative(const string & variable1, const string & variable2) const throw (Exception);
    double d2f(const string & variable1, const string & variable2, const ParameterList & parameters) throw (Exception);
};
} 
