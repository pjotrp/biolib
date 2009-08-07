%module bpp_exceptions
%{
#include "Exceptions.h"
using namespace bpp;
%}

%include "std_except.i"

using namespace std;

%ignore Exception::Exception();

class Exception:public exception
{
  public:
    Exception(const char * text);
    Exception(const string & text);
    virtual ~Exception() throw();
    const char * what() const throw();
};

class IOException:public Exception
{
  public: // Class constructors and destructor:
    IOException(const char * text);
    IOException(const string & text); 
    virtual ~IOException() throw();
};

class NullPointerException:public Exception
{
  public:
    NullPointerException(const char * text);
    NullPointerException(const string & text);
    virtual ~NullPointerException() throw();
};

class ZeroDivisionException:public Exception
{
  public:
    ZeroDivisionException(const char * text);
    ZeroDivisionException(const string & text);
    virtual ~ZeroDivisionException() throw();
};

class BadIntegerException:public Exception
{
  public:
    BadIntegerException(const char * text, int badInt);
    BadIntegerException(const string & text, int badInt);
    virtual ~BadIntegerException() throw();
    int getBadInteger() const;
};

class BadNumberException:public Exception
{
  public:
    BadNumberException(const char * text, double badNumber);
    BadNumberException(const string & text, double badNumber);
    virtual ~BadNumberException() throw();
    double getBadNumber() const;
};

class NumberFormatException:public Exception
{
  public:
    NumberFormatException(const char * text, const string & badNumber);
    NumberFormatException(const string & text, const string & badNumber);
    virtual ~NumberFormatException() throw();
    string getBadNumber() const;
};

class IndexOutOfBoundsException:public BadIntegerException
{
  public:
    IndexOutOfBoundsException(const char *   text, int badInt, int lowerBound, int upperBound);
    IndexOutOfBoundsException(const string & text, int badInt, int lowerBound, int upperBound);
    virtual ~IndexOutOfBoundsException() throw();
    int * getBounds() const;
};
