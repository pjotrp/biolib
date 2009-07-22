%module bpp_
%{
#include "Parameter.h"
using namespace bpp;
%}
%include "ParameterExceptions.i"
%include "Constraints.i"
%include "std_string.i"
%include "std_iostream.i"
using namespace std;
%include "Clonable.i"

class Parameter;

class ParameterEvent:public Clonable
{
  public:
    ParameterEvent(Parameter * parameter);
    Clonable * clone() const;

    const Parameter * getParameter() const;
    Parameter * getParameter();
};

class ParameterListener:public virtual Clonable
{
  public:
    Clonable * clone() const = 0;

    virtual const string & getId() const = 0;
    virtual void parameterNameChanged(ParameterEvent & event) = 0;
    virtual void parameterValueChanged(ParameterEvent & event) = 0;
};

%rename(__assign__) Parameter::operator=;
//%template(paramPVector) std::vector<Parameter*>;
class Parameter:public virtual Clonable
{
  public: 

    Parameter(const string & name = "", double value = 0, Constraint * constraint = NULL, bool attachConstraint = false)
    throw (ConstraintException);
    Parameter(const Parameter & param);
    Parameter & operator=(const Parameter & param);
    virtual ~Parameter();
    Clonable *clone() const;

    virtual void setName(const string & name);
    virtual void setValue(double value) throw (ConstraintException);
    virtual string getName() const;
    virtual double getValue() const;
    virtual const Constraint * getConstraint() const;
    virtual Constraint * getConstraint();
    virtual bool hasConstraint() const;
    virtual const Constraint * removeConstraint();
    virtual void setConstraint(Constraint * constraint) throw (ConstraintException);
    virtual void addParameterListener(ParameterListener * listener, bool attachListener = true);
    virtual void removeParameterListener(const string & listenerId);

    static IncludingPositiveReal R_PLUS;
    static ExcludingPositiveReal R_PLUS_STAR;
    static IncludingNegativeReal R_MINUS;
    static ExcludingNegativeReal R_MINUS_STAR;
    static IncludingInterval PROP_CONSTRAINT_IN;
    static ExcludingInterval PROP_CONSTRAINT_EX;
};
