%module bpp_
%{
#include "Domain.h"
using namespace bpp;
%}
//%include "VectorTools.i"
%include "Exceptions.i"
%include "TextTools.i"

class OutOfRangeException: public Exception
{
  public:
    OutOfRangeException(const string & text, double badValue, double lowerBound, double upperBound):
      Exception(text +
        "Value " +
        TextTools::toString(badValue) + 
        " is out of range [" +
        TextTools::toString(lowerBound) + 
        ", " + 
        TextTools::toString(upperBound) +
        "[."),
      _badValue(badValue), _lowerBound(lowerBound), _upperBound(upperBound);
};

class Domain
{
  public:
    Domain(double a = 0, double b = 0, unsigned int n = 1) throw (Exception);
    Domain(const Vdouble & bounds) throw (Exception);
    Domain(const Vdouble & bounds, const Vdouble & midPoints) throw (Exception);
    virtual ~Domain();

    virtual double getLowerBound() const;
    virtual double getUpperBound() const;
    virtual double getLowerValue() const;
    virtual double getUpperValue() const;
    virtual unsigned int getSize() const;
    virtual const Vdouble & getBounds() const;
    virtual double getBound(unsigned int i) const;
    virtual double getValue(unsigned int i) const;
    virtual double getNearestValue(double x) const throw (OutOfRangeException);
    virtual unsigned int getIndex(double x) const throw (OutOfRangeException);
};
