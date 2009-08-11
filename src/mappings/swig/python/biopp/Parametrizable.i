%module bpp_
%{
#include "Parametrizable.h"
using namespace bpp;
%}
%include "Clonable.i"
%include "std_string.i"
using namespace std;
%include "ParameterList.i"

class Parametrizable:public virtual Clonable
{
  public:
    Parametrizable();
    virtual ~Parametrizable();

    virtual bool hasParameter(const string & name) const = 0;
    virtual const ParameterList & getParameters() const = 0;
    virtual const Parameter & getParameter(const string & name) const throw (ParameterNotFoundException) = 0;
    virtual double getParameterValue(const string & name) const throw (ParameterNotFoundException) = 0;
    virtual void setAllParametersValues(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException) = 0;
    virtual void setParameterValue(const string & name, double value) throw (ParameterNotFoundException, ConstraintException) = 0;
    virtual void setParametersValues(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException) = 0;
    virtual void matchParametersValues(const ParameterList & parameters) throw (ConstraintException) = 0;
    virtual unsigned int getNumberOfParameters() const = 0;
    virtual void setNamespace(const string& prefix) = 0;
    virtual string getNamespace() const = 0;
    virtual string getParameterNameWithoutNamespace(const string& name) const = 0;
};

class ParametrizableAdapter:public virtual Parametrizable
{
  public:
    ParametrizableAdapter();
    virtual ~ParametrizableAdapter();

    bool hasParameter(const string & name) const;
    const ParameterList & getParameters() const;
    const Parameter & getParameter(const string & name) const throw (ParameterNotFoundException);
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
