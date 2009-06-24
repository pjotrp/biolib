%module bpp_exceptions
%{
#include <stdexcept>
%}

%include "std_except.i"

using namespace std;

namespace bpp
{


class Exception:
  public exception
{
  protected:
    string _message;
  
  public:
    Exception(const char * text): _message(string(text)) {}
    Exception(const string & text): _message(text) {}
    virtual ~Exception() throw() {}

  public:
    const char * what() const throw() { return _message.c_str(); }
};

class IOException:
  public Exception
{
  public: // Class constructors and destructor:
    IOException(const char * text): Exception(text) {}
    IOException(const string & text): Exception(text) {} 
    virtual ~IOException() throw() {}
};

class NullPointerException:
  public Exception
{
  public:
    NullPointerException(const char * text): Exception(text) {}
    NullPointerException(const string & text): Exception(text) {}
    virtual ~NullPointerException() throw() {}
};


class ZeroDivisionException:
  public Exception
{
  public:
    ZeroDivisionException(const char * text): Exception(text) {}
    ZeroDivisionException(const string & text): Exception(text) {}
    virtual ~ZeroDivisionException() throw() {}
};

class BadIntegerException:
  public Exception
{
  protected:
    int _badInt;
  
  public:
    BadIntegerException(const char * text, int badInt);
    BadIntegerException(const string & text, int badInt);
    virtual ~BadIntegerException() throw() {}
  public:
    int getBadInteger() const { return _badInt; }
};

class BadNumberException:
  public Exception
{
  protected:
    double _badNumber;
  public:
    BadNumberException(const char * text, double badNumber);
    BadNumberException(const string & text, double badNumber);
    virtual ~BadNumberException() throw() {}
  public:
    double getBadNumber() const { return _badNumber; }
};

class NumberFormatException:
  public Exception
{
  protected:
    string _badNumber;
  public:
    NumberFormatException(const char * text, const string & badNumber);
    NumberFormatException(const string & text, const string & badNumber);
    virtual ~NumberFormatException() throw() {}
  public:
    string getBadNumber() const { return _badNumber; }
};

class IndexOutOfBoundsException:
  public BadIntegerException
{
  protected:
    int _lowerBound, _upperBound;
  public:
    IndexOutOfBoundsException(const char *   text, int badInt, int lowerBound, int upperBound);
    IndexOutOfBoundsException(const string & text, int badInt, int lowerBound, int upperBound);
    virtual ~IndexOutOfBoundsException() throw() {}
  public:
    int * getBounds() const;
};

} //end of namespace bpp.
