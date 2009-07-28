%module bpptest
%{
#include "RateDistributionFactory.h"
using namespace bpp;
%}
#include "distributions"
%include "std_string.i"
using namespace std;

class RateDistributionFactory
{
public:
  static const string CONSTANT_DISTRIBUTION;
  static const string GAMMA_DISTRIBUTION;

  RateDistributionFactory(unsigned int nbClasses = 4): _nbClasses(nbClasses);
  virtual ~RateDistributionFactory();

  virtual DiscreteDistribution * createDiscreteDistribution(const string& distName, unsigned int nbClasses) throw (Exception);
  virtual DiscreteDistribution * createDiscreteDistribution(const string& distName) throw (Exception);
};
