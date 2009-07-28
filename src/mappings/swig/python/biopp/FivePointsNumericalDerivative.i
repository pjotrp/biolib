%module bpp_
%{
#include "FivePointsNumericalDerivative.h"
using namespace bpp;
%}
%include "Functions.i"
%include "AbstractNumericalDerivative.i"
%include "std_map.i"
%include "std_vector.i"
%include "std_string.i"

class FivePointsNumericalDerivative:
  public AbstractNumericalDerivative
{
  public:
    FivePointsNumericalDerivative(Function* function) : AbstractNumericalDerivative(function);
    FivePointsNumericalDerivative(DerivableFirstOrder* function) : AbstractNumericalDerivative(function);
    FivePointsNumericalDerivative(DerivableSecondOrder* function) : AbstractNumericalDerivative(function);
    virtual ~FivePointsNumericalDerivative();
    FivePointsNumericalDerivative* clone() const;

    double getValue() const throw (Exception);
    double getSecondOrderDerivative(const string & variable1, const string & variable2) const throw (Exception);
};
