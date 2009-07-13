%module bpp_
%{
#include "NumTools.h"
%}
%include "Functions.i"
%include "Matrix.i"
namespace bpp
{
class NumTools
{
public:
  template<class T> static T abs(T a);
  template<class T> static T sign(T a);
  template<class T> static T max(T a, T b);
  template<class T> static T min(T a, T b);
  	 
  template<class T> static T sign(T a, T b);
  template<class T> static T sqr(T a);
  template<class T> static T pow(T a, T b);
  template<class T> static void swap(T & a, T & b);
  template<class T> static void shift(T & a, T & b, T c);
  template<class T> static void shift(T & a, T & b, T & c, T d);
  template<class T> static T fact(T n);
  static double uniRoot(Function & f, const string & param, double a, double b, double tolerance) throw (Exception);
  static RowMatrix<double> * computeHessianMatrix(DerivableSecondOrder & function, const ParameterList & parameters);
};
} 
