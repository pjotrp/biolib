%module bpp_
%{
#include "StatTest.h"
%}
%include "Clonable.i"
namespace bpp
{
class StatTest:
  public virtual Clonable
{
  public:
    StatTest();
    virtual ~StatTest();
  public:
    virtual string getName() const = 0;
    virtual double getStatistic() const = 0;
    virtual double getPValue() const = 0;
};
} 
