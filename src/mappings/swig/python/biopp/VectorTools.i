%module bpp_vectools
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

%warnfilter(509) VectorTools;

%ignore VectorTools::VectorTools;
%ignore VectorTools::~VectorTools;

class VectorTools
{
  public:
    VectorTools();
    virtual ~VectorTools();

    template <class T> static vector<T> seq(T from, T to, T by);
    %template(seq) seq<int>;
    %template(seq) seq<double>;

    template<class T> static unsigned int which(const vector<T> & v, const T & which) throw (ElementNotFoundException<T>);
    %template(which) which<int>;
    %template(which) which<double>;

    template<class T> static vector<unsigned int> whichAll(const vector<T> & v, const T & which) throw (ElementNotFoundException<T>);
    %template(whichAll) whichAll<int>;
    %template(whichAll) whichAll<double>;

    template<class T> static vector<T> unique(const vector<T> & v);
    %template(unique) unique<int>;
    %template(unique) unique<double>;

    template<class T> static bool isUnique(const vector<T> & v);
    %template(isUnique) isUnique<int>;
    %template(isUnique) isUnique<double>;

    template<class T> static vector<T> extract(const vector<T> & v1, const vector<int> & v2);
    %template(extract) extract<int>;
    %template(extract) extract<double>;

    template<class T> static map<T, unsigned int> countValues(const vector<T> & v);
    %template(countValues) countValues<int>;
    %template(countValues) countValues<double>;

    static vector<double> breaks(const vector<double> & v, unsigned int n);

    template<class T> static unsigned int nclassScott(const vector<T> & v);
    //%template(nclassScott) nclassScott<int>;
    //%template(nclassScott) nclassScott<double>;
    //%template(nclassScott) nclassScott<unsigned int>;

    template<class T> static T prod(const vector<T> & v1);
    %template(prod) prod<int>;
    %template(prod) prod<double>;

    template<class T> static T sum(const vector<T> & v1);
    %template(sum) sum<int>;
    %template(sum) sum<double>;

    template<class T> static void lognorm(vector<T> & v);
    //%template(lognorm) lognorm<int>;
    //%template(lognorm) lognorm<double>;

    template<class T> static T logsumexp(const vector<T> & v1, const vector<T> & v2);
    //%template(logsumexp) logsumexp<int>;
    //%template(logsumexp) logsumexp<double>;

    template<class T> static vector<double> log(const vector<T> & v1);
    template<class T> static vector<double> log(const vector<T> & v1, double base);
    %template(log) log<int>;
    %template(log) log<double>;

    template<class T> static vector<double> exp(const vector<T> & v1);
    %template(exp) exp<int>;
    %template(exp) exp<double>;

    template<class T> static vector<double> log10(const vector<T> & v1);
    %template(log10) log10<int>;
    %template(log10) log10<double>;

    template<class T> static vector<T> fact(const vector<T> & v1);
    %template(fact) fact<int>;
    %template(fact) fact<double>;

    template<class T> static vector<T> sqr(const vector<T> & v1);
    %template(sqr) sqr<int>;
    %template(sqr) sqr<double>;

    template<class T> static vector<T> pow(const vector<T> & v1, T & b);
    %template(pow) pow<int>;
    %template(pow) pow<double>;

    template<class T> static string paste(const vector<T> & v, const string & delim = " ");
    %template(paste) paste<int>;
    %template(paste) paste<double>;

    %rename(_print) print;
    template<class T> static void print(const vector<T> & v1, ostream & out = cout, const string & delim = " ");
    %template(intPrint) print<int>;
    %template(dblPrint) print<double>;

    template<class InputType, class OutputType> static OutputType scalar(const vector<InputType> & v1, const vector<InputType> & v2) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType scalar(const vector<InputType> & v1, const vector<InputType> & v2, const vector<InputType> & w) throw (DimensionException);
    //%template(iiScalar) scalar<int,int>;
    //%template(idScalar) scalar<int,double>;
    //%template(diScalar) scalar<double,int>;
    //%template(ddScalar) scalar<double,double>;

    template<class T> static vector<T> kroneckerMult(const vector<T> & v1, const vector<T> & v2) throw (DimensionException);
    %template(kroneckerMult) kroneckerMult<int>;
    %template(kroneckerMult) kroneckerMult<double>;

    template<class InputType, class OutputType> static OutputType norm(const vector<InputType> & v1);
    template<class InputType, class OutputType> static OutputType norm(const vector<InputType> & v1, const vector<InputType> & w) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType cos(const vector<InputType> & v1, const vector<InputType> & v2) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType cos(const vector<InputType> & v1, const vector<InputType> & v2, const vector<InputType> & w) throw (DimensionException);

    template<class T> static T min(const vector<T> & v) throw (EmptyVectorException<T>);
    %template(min) min<int>;
    %template(min) min<double>;

    template<class T> static T max(const vector<T> & v) throw (EmptyVectorException<T>);
    %template(max) max<int>;
    %template(max) max<double>;

    template<class T> static unsigned int posmin(const vector<T> & v) throw (EmptyVectorException<T>);
    %template(posmin) posmin<int>;
    %template(posmin) posmin<double>;

    template<class T> static unsigned int whichmax(const vector<T> & v) throw (EmptyVectorException<T>);
    %template(whichmax) whichmax<int>;
    %template(whichmax) whichmax<double>;

    template<class T> static vector<T> range(const vector<T> & v) throw (EmptyVectorException<T>);
    %template(range) range<int>;
    %template(range) range<double>;

    template<class InputType, class OutputType> static OutputType mean(const vector<InputType> & v1);
    template<class InputType, class OutputType> static OutputType mean(const vector<InputType> & v1, const vector<InputType> & w, bool normalizeWeights = true);

    template<class InputType> static InputType median(vector<InputType> & v1);
    %template(median) median<int>;
    %template(median) median<double>;

    //%ignore center;
    //%ignore cov;
    //%ignore var;
    //%ignore sd;

    template<class InputType, class OutputType> static vector<OutputType> center(const vector<InputType> & v1);
    template<class InputType, class OutputType> static vector<OutputType> center(const vector<InputType> & v1, const vector<InputType> & w, bool normalizeWeights = true);
    template<class InputType, class OutputType> static OutputType cov(const vector<InputType> & v1, const vector<InputType> & v2, bool unbiased = true) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType cov(const vector<InputType> & v1, const vector<InputType> & v2, const vector<InputType> & w, bool unbiased = true, bool normalizeWeights = true) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType var(const vector<InputType> & v1, bool unbiased = true);
    template<class InputType, class OutputType> static OutputType var(const vector<InputType> & v1, const vector<InputType> & w, bool unbiased = true, bool normalizeWeights = true) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType sd(const vector<InputType> & v1, bool unbiased = true);
    //%template(sd) sd<int,int>;
    //%template(sd) sd<int,double>;
    //%template(sd) sd<double,int>;
    //%template(sd) sd<double,double>;

    template<class InputType, class OutputType> static OutputType sd(const vector<InputType> & v1, const vector<InputType> & w, bool unbiased = true, bool normalizeWeights = true) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType cor(const vector<InputType> & v1, const vector<InputType> & v2) throw (DimensionException);
    template<class InputType, class OutputType> static OutputType cor(const vector<InputType> & v1, const vector<InputType> & v2, const vector<InputType> & w, bool normalizeWeights = true) throw (DimensionException);
    template<class InputType, class OutputType> static double shannon(const vector<InputType> & v, double base = 2.7182818);

    template<class T> static bool haveSameElements(const vector<T> & v1, const vector<T> & v2);
    template<class T> static bool haveSameElements(vector<T> & v1, vector<T> & v2);
    //%template(haveSameElements) haveSameElements<int>;
    //%template(haveSameElements) haveSameElements<double>;

    template<class T> static bool contains(const vector<T> & vec, T el);
    //%template(contains) contains<int>;
    //%template(contains) contains<double>;

    template<class T> static bool containsAll(vector<T> & v1, vector<T> & v2);
    //%template(containsAll) containsAll<int>;
    //%template(containsAll) containsAll<double>;

    template<class T> static vector<T> vectorUnion(const vector<T> & vec1, const vector<T> & vec2);
    template<class T> static vector<T> vectorUnion(const vector< vector<T> > & vecElementL);
    //%template(vectorUnion) vectorUnion<int>;
    //%template(vectorUnion) vectorUnion<double>;

    template<class T> static vector<T> vectorIntersection(const vector<T> & vec1, const vector<T> & vec2);
    template<class T> static vector<T> vectorIntersection(const vector< vector<T> > & vecElementL);
    //%template(vectorIntersection) vectorIntersection<int>;
    //%template(vectorIntersection) vectorIntersection<double>;

    template<class T> static void append(vector<T> & vec1, const vector<T> & vec2);
    template<class T> static vector<T> append(const vector< vector<T> > & vecElementL);
    //%template(append) append<int>;
    //%template(append) append<double>;

    template<class T> static void diff(vector<T> & v1, vector<T> & v2, vector<T> & v3);
    //%template(diff) diff<int>;
    //%template(diff) diff<double>;

    static bool test();
};
