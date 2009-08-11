%module bpp_
%{
#include "NumTools.h"
using namespace bpp;
%}
%include "Functions.i"
%include "Matrix.i"

%ignore NumTools::NumTools;
%ignore NumTools::~NumTools;

class NumTools
{
public:
  template<class T> static T abs(T a);
  %template(abs) abs<int>;
  %template(abs) abs<double>;

  template<class T> static T sign(T a);
  template<class T> static T sign(T a, T b);
  %template(sign) sign<int>;
  %template(sign) sign<double>;

  template<class T> static T max(T a, T b);
  %template(max) max<int>;
  %template(max) max<double>;

  template<class T> static T min(T a, T b);
  %template(min) min<int>;
  %template(min) min<double>;
  	 
  //%template(sign) sign<int>;
  //%template(sign) sign<double>;

  template<class T> static T sqr(T a);
  %template(sqr) sqr<int>;
  %template(sqr) sqr<double>;

  template<class T> static T pow(T a, T b);
  %template(pow) pow<int>;
  %template(pow) pow<double>;

  template<class T> static void swap(T & a, T & b);
  %template(swap) swap<int>;
  %template(swap) swap<double>;

  template<class T> static void shift(T & a, T & b, T c);
  template<class T> static void shift(T & a, T & b, T & c, T d);
  %template(shift) shift<int>;
  %template(shift) shift<double>;

  template<class T> static T fact(T n);
  %template(fact) fact<int>;
  %template(fact) fact<double>;

  static double uniRoot(Function & f, const string & param, double a, double b, double tolerance) throw (Exception);
  static RowMatrix<double> * computeHessianMatrix(DerivableSecondOrder & function, const ParameterList & parameters);
};
