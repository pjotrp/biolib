%module bpp_
%{
#include "AbstractParametrizable.h"
using namespace bpp;
%}
%include "Parametrizable.i"
%include "std_map.i"
using namespace std;

class AbstractParametrizable:public virtual Parametrizable
{
  public:
    AbstractParametrizable(const string& prefix) : prefix_(prefix);
    virtual ~AbstractParametrizable();

    bool hasParameter(const string & name) const;
    const ParameterList & getParameters() const;
    const Parameter & getParameter(const string & name) const throw (ParameterNotFoundException);
    double getParameterValue(const string & name) const throw (ParameterNotFoundException);
    void setAllParametersValues(const ParameterList & parameters)  throw (ParameterNotFoundException, ConstraintException);
    void setParameterValue(const string & name, double value)  throw (ParameterNotFoundException, ConstraintException);
    void setParametersValues(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    void matchParametersValues(const ParameterList & parameters) throw (ConstraintException);
    unsigned int getNumberOfParameters() const;
    void setNamespace(const string& prefix);
    string getNamespace() const;
    string getParameterNameWithoutNamespace(const string& name) const;
    virtual void fireParameterChanged(const ParameterList & parameters) = 0;
};
