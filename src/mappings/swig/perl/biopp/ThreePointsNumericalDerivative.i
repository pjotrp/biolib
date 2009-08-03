%module bpp_
%{
#include "ThreePointsNumericalDerivative.h"
using namespace bpp;
%}
%include "Functions.i"
%include "AbstractNumericalDerivative.i"
%include "std_map.i"
%include "std_vector.i"
%include "std_string.i"

class ThreePointsNumericalDerivative:
  public AbstractNumericalDerivative
{
  public:
    ThreePointsNumericalDerivative (Function * function): AbstractNumericalDerivative(function);
    ThreePointsNumericalDerivative (DerivableFirstOrder * function): AbstractNumericalDerivative(function);
    ThreePointsNumericalDerivative (DerivableSecondOrder * function): AbstractNumericalDerivative(function);
    virtual ~ThreePointsNumericalDerivative();
    ThreePointsNumericalDerivative* clone() const;

    double getValue() const throw (Exception);
};
