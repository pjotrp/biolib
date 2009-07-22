%module bpp_
%{
#include "TransformedParameter.h"
using namespace bpp;
%}
%include "Parameter.i"
%include "NumConstants.i"

using namespace std;

class TransformedParameter:public virtual Parameter
{
	public:
		TransformedParameter * clone() const = 0;
    virtual void setOriginalValue(double value) throw (ConstraintException) = 0;
    virtual double getOriginalValue() const = 0;
};

class RTransformedParameter:public virtual TransformedParameter
{
  public:
    RTransformedParameter(const string & name, double value, double bound = 0, bool positive = true, double scale = 1):Parameter(name, 1.),_scale(scale),_bound(bound),_positive(positive);
    RTransformedParameter * clone() const;

    void setOriginalValue(double value) throw (ConstraintException);
    double getOriginalValue() const;
};

class IntervalTransformedParameter:public virtual TransformedParameter
{
  public:
    IntervalTransformedParameter(const string & name, double value, double lowerBound = 0, double upperBound = 1, double scale = 1, bool hyper = true):Parameter(name, hyper ? scale * atanh(2. * (value - lowerBound) / (upperBound - lowerBound) - 1.) : scale * tan(3.141593 * (value - lowerBound)/(upperBound - lowerBound) - 1.570796)),_scale(scale),_lowerBound(lowerBound),_upperBound(upperBound),_hyper(hyper),_tiny(NumConstants::TINY);
//  Parameter(name, hyper ? 
//scale * atanh(2. * (value - lowerBound) / (upperBound - lowerBound) - 1.) : 
//scale * tan(3.141593 * (value - lowerBound)/(upperBound - lowerBound) - 1.570796)),
//_scale(scale),_lowerBound(lowerBound),_upperBound(upperBound),_hyper(hyper),_tiny(NumConstants::TINY);



    IntervalTransformedParameter * clone() const;

    void setOriginalValue(double value) throw (ConstraintException);
    double getOriginalValue() const;
};

class PlaceboTransformedParameter:
  public virtual TransformedParameter
{
  public:
    PlaceboTransformedParameter(const string & name, double value):Parameter(name, value);
    PlaceboTransformedParameter * clone() const;

    void setOriginalValue(double value) throw (ConstraintException);
    double getOriginalValue() const;
};
