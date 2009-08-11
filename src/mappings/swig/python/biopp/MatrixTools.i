%module bpp_
%{
#include "MatrixTools.h"
using namespace bpp;
%}
//%include "VectorTools.i"
%include "Matrix.i"
%include "LUDecomposition.i"
%include "EigenValue.i"
//#include <cstdio>
%include "std_iostream.i"
using namespace std;

%ignore MatrixTools::MatrixTools;
%ignore MatrixTools::~MatrixTools;

class MatrixTools
{
  public:
    MatrixTools();
    ~MatrixTools();
    template<class MatrixA, class MatrixO> static void copy(const MatrixA & A, MatrixO & O);
    %template(copy) copy<Matrix<int>, Matrix<int> >;
    %template(copy) copy<Matrix<int>, Matrix<double> >;
    %template(copy) copy<Matrix<double>, Matrix<int> >;
    %template(copy) copy<Matrix<double>, Matrix<double> >;

    template<class Matrix> static void getId(unsigned int n, Matrix & O);
    %template(getId) getId< Matrix<int> >;
    %template(getId) getId< Matrix<double> >;

    template<class Scalar> static void diag(const vector<Scalar> & D, Matrix<Scalar> & O);
    template<class Scalar> static void diag(const Matrix<Scalar> & M, vector<Scalar> & O) throw (DimensionException);
    %template(diag) diag<int>;
    %template(diag) diag<double>;

    template<class Matrix, class Scalar> static void fill(Matrix & M, Scalar x);
    %template(fill) fill<Matrix<int>, int>;
    %template(fill) fill<Matrix<double>, double>;

    template<class Matrix, class Scalar> static void scale(Matrix & A, Scalar a, Scalar b = 0);
    %template(scale) scale<Matrix<int>, int>;
    %template(scale) scale<Matrix<double>, double>;

    template<class Scalar> static void mult(const Matrix<Scalar> & A, const Matrix<Scalar> & B, Matrix<Scalar> & O) throw (DimensionException);
    //template<class Scalar> static void mult(const Matrix<Scalar> & A, const vector<Scalar> & D, const Matrix<Scalar> & B, Matrix<Scalar> & O) throw (DimensionException);
    %template(mult) mult<int>;
    %template(mult) mult<double>;

    template<class MatrixA, class MatrixB> static void add(MatrixA & A, const MatrixB & B) throw (DimensionException);
    %template(add) add<Matrix<int>, Matrix<int> >;
    %template(add) add<Matrix<int>, Matrix<double> >;
    %template(add) add<Matrix<double>, Matrix<int> >;
    %template(add) add<Matrix<double>, Matrix<double> >;

    template<class Matrix> static void pow(const Matrix & A, unsigned int p, Matrix & O) throw (DimensionException);
    //%template(pow) pow< Matrix<int> >;
    %template(pow) pow< Matrix<double> >;

    template<class Scalar> static void exp(const Matrix<Scalar> & A, Matrix<Scalar> & O) throw (DimensionException);
    //%template(exp) exp<int>;
    %template(exp) exp<double>;

    template<class Matrix> static vector<unsigned int> whichmax(const Matrix & m);
    %template(whichmax) whichmax< Matrix<int> >;
    %template(whichmax) whichmax< Matrix<double> >;

    template<class Matrix> static vector<unsigned int> whichmin(const Matrix & m);
    %template(whichmin) whichmin< Matrix<int> >;
    %template(whichmin) whichmin< Matrix<double> >;

    %rename(_print) print;
    template<class Matrix> static void print(const Matrix & m, ostream & out = cout);
    %template(_print) print< Matrix<int> >;
    %template(_print) print< Matrix<double> >;

    template<class Real> static void print(const vector<Real> & v, ostream & out = cout);
    //%template(_print) print<int>;  // these not really necessary in scripting languages
    //%template(printDoubleVector) print<double>;
    
    template<class Matrix> static bool isSquare(const Matrix & A);
    %template(isSquare) isSquare< Matrix<int> >;
    %template(isSquare) isSquare< Matrix<double> >;

    template<class Scalar> static void inv(const Matrix<Scalar> & A, Matrix<Scalar> & O) throw (DimensionException);
    %template(inv) inv<int>;
    %template(inv) inv<double>;

    template<class MatrixA, class MatrixO> static void transpose(const MatrixA & A, MatrixO & O);
    %template(transpose) transpose<Matrix<int>, Matrix<int> >;
    %template(transpose) transpose<Matrix<int>, Matrix<double> >;
    %template(transpose) transpose<Matrix<double>, Matrix<int> >;
    %template(transpose) transpose<Matrix<double>, Matrix<double> >;

    template<class Scalar> static void kroneckerMult(const Matrix<Scalar> & A, const Matrix<Scalar> & B, Matrix<Scalar> & O);
    %template(kroneckerMult) kroneckerMult<int>;
    %template(kroneckerMult) kroneckerMult<double>;

    template<class Scalar> static void kroneckerSum(const Matrix<Scalar> & A, const Matrix<Scalar> & B, Matrix<Scalar> & O);
    template<class Scalar> static void kroneckerSum(const vector< Matrix<Scalar> *> & vA, Matrix<Scalar> & O);
    %template(kroneckerSum) kroneckerSum<int>;
    %template(kroneckerSum) kroneckerSum<double>;
};
