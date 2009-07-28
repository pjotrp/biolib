%module bpptest
%{
#include "PseudoNewtonOptimizer.h"
using namespace bpp;
%}
%include "AbstractOptimizer.i"

class PseudoNewtonOptimizer:public AbstractOptimizer
{
  public:
    PseudoNewtonOptimizer(DerivableSecondOrder * function);
    virtual ~PseudoNewtonOptimizer();
    PseudoNewtonOptimizer* clone() const;

    double getFunctionValue() const throw (NullPointerException);
    void doInit(const ParameterList & params) throw (Exception);
    double doStep() throw (Exception);
    void setMaximumNumberOfCorrections(unsigned int mx);
};
