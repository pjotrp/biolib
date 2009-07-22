%module bpp_vectortools
%{
#include "VectorTools.h"
using namespace bpp;
%}
%include "VectorExceptions.i"
%include "NumTools.i"
%include "std_vector.i"
%include "std_map.i"
%include "std_iostream.i"
//#include <cmath>
//#include <algorithm>

using namespace std;

typedef vector<double> Vdouble;
typedef vector<Vdouble> VVdouble;
typedef vector<VVdouble> VVVdouble;
typedef vector<VVVdouble> VVVVdouble;
typedef vector<int> Vint;
typedef vector<Vint> VVint;
typedef vector<VVint> VVVint;
typedef vector<VVVint> VVVVint;

template<class T> vector<T> operator+ (const vector<T> & v1, const vector<T> & v2) throw (DimensionException);
template<class T> vector<T> operator- (const vector<T> & v1, const vector<T> & v2) throw (DimensionException);
template<class T> vector<T> operator* (const vector<T> & v1, const vector<T> & v2) throw (DimensionException);
template<class T> vector<T> operator/ (const vector<T> & v1, const vector<T> & v2) throw (DimensionException);
template<class T, class C> vector<T> operator+ (const vector<T> & v1, const C & c);
template<class T, class C> vector<T> operator+ (const C & c, const vector<T> & v1);
template<class T, class C> vector<T> operator- (const vector<T> & v1, const C & c);
template<class T, class C> vector<T> operator- (const C & c, const vector<T> & v1);
template<class T, class C> vector<T> operator* (const vector<T> & v1, const C & c);
template<class T, class C> vector<T> operator* (const C & c, const vector<T> & v1);
template<class T, class C> vector<T> operator/ (const vector<T> & v1, const C & c);
template<class T, class C> vector<T> operator/ (const C & c, const vector<T> & v1);
template<class T> void operator+= (vector<T> & v1, const vector<T> & v2) throw (DimensionException);
template<class T> void operator-= (vector<T> & v1, const vector<T> & v2) throw (DimensionException);
template<class T> void operator*= (vector<T> & v1, const vector<T> & v2) throw (DimensionException);
template<class T> void operator/= (vector<T> & v1, const vector<T> & v2) throw (DimensionException);
template<class T, class C> void operator+= (vector<T> & v1, const C & c);
template<class T, class C> void operator-= (vector<T> & v1, const C & c);
template<class T, class C> void operator*= (vector<T> & v1, const C & c);
template<class T, class C> void operator/= (vector<T> & v1, const C & c);

class VectorTools
{
  public:
    VectorTools();
    virtual ~VectorTools();

    template <class T> static vector<T> seq(T from, T to, T by);
    template<class T> static unsigned int which(const vector<T> & v, const T & which) throw (ElementNotFoundException<T>);
    template<class T> static vector<unsigned int> whichAll(const vector<T> & v, const T & which) throw (ElementNotFoundException<T>);
    template<class T> static vector<T> unique(const vector<T> & v);
    template<class T> static bool isUnique(const vector<T> & v);
  template<class T> static vector<T> extract(const vector<T> & v1, const vector<int> & v2);
    template<class T> static map<T, unsigned int> countValues(const vector<T> & v);
    static vector<double> breaks(const vector<double> & v, unsigned int n);
    template<class T> static unsigned int nclassScott(const vector<T> & v);
    template<class T> static T prod(const vector<T> & v1);
    template<class T> static T sum(const vector<T> & v1);
    template<class T> static void lognorm(vector<T> & v);
    template<class T> static T logsumexp(const vector<T> & v1, const vector<T> & v2);
    template<class T> static vector<double> log(const vector<T> & v1);
    template<class T> static vector<double> log(const vector<T> & v1, double base);
    template<class T> static vector<double> exp(const vector<T> & v1);
    template<class T> static vector<double> log10(const vector<T> & v1);
    template<class T> static vector<T> fact(const vector<T> & v1);
    template<class T> static vector<T> sqr(const vector<T> & v1);
    template<class T> static vector<T> pow(const vector<T> & v1, T & b);
    template<class T> static string paste(const vector<T> & v, const string & delim = " ");
    template<class T> static void print(const vector<T> & v1, ostream & out = cout, const string & delim = " ");
    template<class InputType, class OutputType> static OutputType scalar(const vector<InputType> & v1, const vector<InputType> & v2) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType scalar(const vector<InputType> & v1, const vector<InputType> & v2, const vector<InputType> & w) throw (DimensionException);
    template<class T> static vector<T> kroneckerMult(const vector<T> & v1, const vector<T> & v2) throw (DimensionException);

    template<class InputType, class OutputType> static OutputType norm(const vector<InputType> & v1);
    template<class InputType, class OutputType> static OutputType norm(const vector<InputType> & v1, const vector<InputType> & w) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType cos(const vector<InputType> & v1, const vector<InputType> & v2) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType cos(const vector<InputType> & v1, const vector<InputType> & v2, const vector<InputType> & w) throw (DimensionException);
    template<class T> static T min(const vector<T> & v) throw (EmptyVectorException<T>);
    template<class T> static T max(const vector<T> & v) throw (EmptyVectorException<T>);
    template<class T> static unsigned int posmin(const vector<T> & v) throw (EmptyVectorException<T>);
    template<class T> static unsigned int whichmax(const vector<T> & v) throw (EmptyVectorException<T>);
    template<class T> static vector<T> range(const vector<T> & v) throw (EmptyVectorException<T>);
    template<class InputType, class OutputType> static OutputType mean(const vector<InputType> & v1);
    template<class InputType, class OutputType> static OutputType mean(const vector<InputType> & v1, const vector<InputType> & w, bool normalizeWeights = true);
    template<class InputType> static InputType median(vector<InputType> & v1);
    template<class InputType, class OutputType> static vector<OutputType> center(const vector<InputType> & v1);
    template<class InputType, class OutputType> static vector<OutputType> center(const vector<InputType> & v1, const vector<InputType> & w, bool normalizeWeights = true);
    template<class InputType, class OutputType> static OutputType cov(const vector<InputType> & v1, const vector<InputType> & v2, bool unbiased = true) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType cov(const vector<InputType> & v1, const vector<InputType> & v2, const vector<InputType> & w, bool unbiased = true, bool normalizeWeights = true) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType var(const vector<InputType> & v1, bool unbiased = true);
    template<class InputType, class OutputType> static OutputType var(const vector<InputType> & v1, const vector<InputType> & w, bool unbiased = true, bool normalizeWeights = true) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType sd(const vector<InputType> & v1, bool unbiased = true);
    template<class InputType, class OutputType> static OutputType sd(const vector<InputType> & v1, const vector<InputType> & w, bool unbiased = true, bool normalizeWeights = true) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType cor(const vector<InputType> & v1, const vector<InputType> & v2) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType cor(const vector<InputType> & v1, const vector<InputType> & v2, const vector<InputType> & w, bool normalizeWeights = true) throw (DimensionException);
    template<class InputType, class OutputType> static double shannon(const vector<InputType> & v, double base = 2.7182818);
    template<class T> static bool haveSameElements(const vector<T> & v1, const vector<T> & v2);
    template<class T> static bool haveSameElements(vector<T> & v1, vector<T> & v2);
    template<class T> static bool contains(const vector<T> & vec, T el);
    template<class T> static bool containsAll(vector<T> & v1, vector<T> & v2);
    template<class T> static vector<T> vectorUnion(const vector<T> & vec1, const vector<T> & vec2);
    template<class T> static vector<T> vectorUnion(const vector< vector<T> > & vecElementL);
    template<class T> static vector<T> vectorIntersection(const vector<T> & vec1, const vector<T> & vec2);
    template<class T> static vector<T> vectorIntersection(const vector< vector<T> > & vecElementL);
    template<class T> static void append(vector<T> & vec1, const vector<T> & vec2);
    template<class T> static vector<T> append(const vector< vector<T> > & vecElementL);
    template<class T> static void diff(vector<T> & v1, vector<T> & v2, vector<T> & v3);
    static bool test();

    %template(intDiff) diff<int>;
    %template(doubleDiff) diff<double>;

};
