%module bpp_
%{
#include "DownhillSimplexMethod.h"
%}
%include "AbstractOptimizer.i"
%include "VectorTools.i"
//#include <cmath>
using namespace std;
namespace bpp
{
class DownhillSimplexMethod:public AbstractOptimizer
{
  public:
    class DSMStopCondition: public AbstractOptimizationStopCondition
    {
      public:
        DSMStopCondition(DownhillSimplexMethod * dsm):AbstractOptimizationStopCondition(dsm);
        virtual ~DSMStopCondition();
        DSMStopCondition* clone() const;

        void init();
        bool isToleranceReached() const;
    };
  friend class DSMStopCondition;

    DownhillSimplexMethod(Function * function);
    virtual ~DownhillSimplexMethod();
    DownhillSimplexMethod* clone() const;

    double optimize() throw (Exception);
    void doInit(const ParameterList & params) throw (Exception);
    double doStep() throw (Exception);
};
} 
