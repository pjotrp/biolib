%module bpp_
%{
#include "TwoPointsNumericalDerivative.h"
%}
%include "Functions.i"
%include "AbstractNumericalDerivative.i"
%include "std_map.i"
%include "std_vector.i"
%include "std_string.i"
namespace bpp
{
class TwoPointsNumericalDerivative:
  public AbstractNumericalDerivative
{
  public:
    TwoPointsNumericalDerivative(Function * function): AbstractNumericalDerivative(function);
    TwoPointsNumericalDerivative(DerivableFirstOrder * function): AbstractNumericalDerivative(function);
    virtual ~TwoPointsNumericalDerivative();
    TwoPointsNumericalDerivative* clone() const;

    double getValue() const throw (Exception);
    double getSecondOrderDerivative(const string & variable) const throw (Exception);
    double getSecondOrderDerivative(const string & variable1, const string & variable2) const throw (Exception);
};
} 
