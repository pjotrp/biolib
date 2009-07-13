%module bpp_
%{
#include "DirectionFunction.h"
%}
%include "Functions.i"
%include "Parametrizable.i"
%include "AutoParameter.i"
namespace bpp
{
class DirectionFunction:public Function,public ParametrizableAdapter
{
  public:
    DirectionFunction(Function * function = NULL): _function(function), _constraintPolicy(AutoParameter::CONSTRAINTS_KEEP), _messenger(&cout);
    virtual ~DirectionFunction();
     DirectionFunction* clone() const;

    void setParameters(const ParameterList & parameters) throw (ParameterNotFoundException, ConstraintException);
    double getValue() const throw (Exception);
    const ParameterList & getParameters() const throw (Exception);

    void init(const ParameterList & p, const vector<double> & xi);
    void autoParameter();
    void ignoreConstraints();
    void setConstraintPolicy(const string & constraintPolicy);
    string getConstraintPolicy() const;
    void setMessageHandler(ostream * messenger);
    Function * getFunction() const;
    ParameterList getFunctionParameters() const;
    unsigned int getNumberOfParameters() const;
};
} 
