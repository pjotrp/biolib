%module bpp_
%{
#include "AbstractDiscreteDistribution.h"
%}
%include "DiscreteDistribution.i"
%include "AbstractParameterAliasable.i"
%include "std_map.i"
using namespace std;
namespace bpp
{
class AbstractDiscreteDistribution:public DiscreteDistribution,public AbstractParameterAliasable
{
  public:
		class Order
    {
      public:
        bool operator() (double l1, double l2) const;
    };

		AbstractDiscreteDistribution(const string& prefix = "") : AbstractParameterAliasable(prefix);
    virtual ~AbstractDiscreteDistribution();

    unsigned int getNumberOfCategories() const;
		double getCategory(unsigned int categoryIndex) const;
		double getProbability(unsigned int categoryIndex) const;
		double getProbability(double category) const;
		Vdouble getCategories() const;
		Vdouble getProbabilities() const;
		void set(double category, double probability);
		void add(double category, double probability);
		double  getInfCumulativeProbability(double category) const;
		double getIInfCumulativeProbability(double category) const;
		double  getSupCumulativeProbability(double category) const;
		double getSSupCumulativeProbability(double category) const;
		double rand() const;
		double randC() const throw (Exception);
		void print(ostream & out) const;
};
} 
