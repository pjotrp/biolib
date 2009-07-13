%module bpp_
%{
#include "ReparametrizationFunctionWrapper.h"
%}
%include "Functions.i"
%include "AbstractParametrizable.i"
%include "TransformedParameter.i"
namespace bpp {
class ReparametrizationFunctionWrapper:
  public virtual Function,
  public AbstractParametrizable
{
  public:
    ReparametrizationFunctionWrapper(Function * function, bool verbose=true);
    virtual ~ReparametrizationFunctionWrapper();
    ReparametrizationFunctionWrapper * clone() const;

    void setParameters(const ParameterList & parameters)
      throw (ParameterNotFoundException, ConstraintException);
    double getValue() const throw (Exception);
    void fireParameterChanged (const ParameterList &parameters);
};
} 
