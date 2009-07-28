%module bpp_
%{
#include "StatTest.h"
using namespace bpp;
%}
%include "Clonable.i"

class StatTest:public virtual Clonable
{
  public:
    StatTest();
    virtual ~StatTest();

    virtual string getName() const = 0;
    virtual double getStatistic() const = 0;
    virtual double getPValue() const = 0;
};
