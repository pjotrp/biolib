%module bpp_
%{
#include "DiscreteDistribution.h"
using namespace bpp;
%}
//%include "VectorTools.i"
%include "ParameterAliasable.i"
%include "Domain.i"
//%include "std_iostream.i"
using namespace std;

%rename(_print) DiscreteDistribution::print;

class DiscreteDistribution:public virtual ParameterAliasable
{
  public:
    DiscreteDistribution();
    virtual ~DiscreteDistribution();
    DiscreteDistribution * clone() const = 0;

    virtual unsigned int getNumberOfCategories() const = 0;
    virtual double getCategory(unsigned int categoryIndex) const = 0;
    virtual double getProbability(unsigned int categoryIndex) const = 0;
    virtual double getProbability(double category) const = 0;
    virtual Vdouble getCategories() const = 0;
    virtual Vdouble getProbabilities() const = 0;
    virtual void set(double category, double probability) = 0;
    virtual void add(double category, double probability) = 0;
    virtual double  getInfCumulativeProbability(double category) const = 0;
    virtual double getIInfCumulativeProbability(double category) const = 0;
    virtual double  getSupCumulativeProbability(double category) const = 0;
    virtual double getSSupCumulativeProbability(double category) const = 0;
    virtual double rand() const = 0;
    virtual double randC() const throw (Exception) = 0;
    virtual Domain getDomain() const = 0;
    virtual void print(ostream & out) const = 0;
};
