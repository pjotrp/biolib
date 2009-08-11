%module bpp
%{
#include "ParameterExceptions.h"
using namespace bpp;
%}
%include "Exceptions.i"
%include "std_string.i"
%include "Parameter.i"
using namespace std;

//class Parameter;
class ParameterException : public Exception {
  public:  
    ParameterException(const char * text, const Parameter * param);
    ParameterException(const string & text, const Parameter * param);
    virtual ~ParameterException() throw ();

    virtual const Parameter * getParameter() const;
};

class ConstraintException : public ParameterException {
  public: 
    ConstraintException(const char *   text, const Parameter * param, double badValue);
    ConstraintException(const string & text, const Parameter * param, double badValue);
    virtual ~ConstraintException() throw ();

    virtual double getBadValue() const;
};

class ParameterNotFoundException : public Exception {
  public:  
    ParameterNotFoundException(const char *   text, const string & param = "");
    ParameterNotFoundException(const string & text, const string & param = "");
    virtual ~ParameterNotFoundException() throw ();
  public:
    virtual string getParameter() const;    
};
