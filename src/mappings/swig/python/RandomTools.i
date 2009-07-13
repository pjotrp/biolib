%module bpp_
%{
#include "RandomTools.h"
%}
//#include <cmath>
//#include <cassert>
//#include <ctime>
%include "std_vector.i"
using namespace std;
%include "RandomFactory.i"
%include "Exceptions.i"
namespace bpp
{
class RandomTools
{
  public:
    RandomTools();
    virtual ~RandomTools();

    static RandomFactory * DEFAULT_GENERATOR;
    static double giveRandomNumberBetweenZeroAndEntry(double entry, const RandomFactory * generator = DEFAULT_GENERATOR);
    static bool flipCoin(const RandomFactory * generator = DEFAULT_GENERATOR);
    static int giveIntRandomNumberBetweenZeroAndEntry(int entry, const RandomFactory * generator = DEFAULT_GENERATOR);
    static void setSeed(long seed);
    static double randGaussian(double mean, double variance, const RandomFactory * generator = DEFAULT_GENERATOR);
    static double randGamma(double dblAlpha, const RandomFactory * generator = DEFAULT_GENERATOR);
    static double randGamma(double alpha, double beta, const RandomFactory * generator = DEFAULT_GENERATOR);
    static double randExponential(double mean, const RandomFactory * generator = DEFAULT_GENERATOR);
    template<class T> 
    static vector<T> getSample(const vector<T> & v, unsigned int size, bool replace = false) throw (IndexOutOfBoundsException)
    static vector<unsigned int> randMultinomial(unsigned int n, const vector<double>& probs);
    static double qNorm(double prob);
    static double lnGamma (double alpha);
    static double incompleteGamma(double x, double alpha, double ln_gamma_alpha);
    static double qChisq(double prob, double v);
    static double pChisq(double x, double v);
    static double qGamma(double prob, double alpha, double beta);
    static double pGamma(double x, double alpha, double beta);
};
} 
