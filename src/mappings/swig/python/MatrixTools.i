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

class MatrixTools
{
	public:
		MatrixTools();
		~MatrixTools();
		template<class MatrixA, class MatrixO> static void copy(const MatrixA & A, MatrixO & O);
		template<class Matrix> static void getId(unsigned int n, Matrix & O);
		template<class Scalar> static void diag(const vector<Scalar> & D, Matrix<Scalar> & O);
		template<class Scalar> static void diag(const Matrix<Scalar> & M, vector<Scalar> & O) throw (DimensionException);
		template<class Matrix, class Scalar> static void fill(Matrix & M, Scalar x);
		template<class Matrix, class Scalar> static void scale(Matrix & A, Scalar a, Scalar b = 0);
		template<class Scalar> static void mult(const Matrix<Scalar> & A, const Matrix<Scalar> & B, Matrix<Scalar> & O) throw (DimensionException);
		template<class Scalar> static void mult(const Matrix<Scalar> & A, const vector<Scalar> & D, const Matrix<Scalar> & B, Matrix<Scalar> & O) throw (DimensionException);
		template<class MatrixA, class MatrixB> static void add(MatrixA & A, const MatrixB & B) throw (DimensionException);
		template<class Matrix> static void pow(const Matrix & A, unsigned int p, Matrix & O) throw (DimensionException);
		template<class Scalar> static void exp(const Matrix<Scalar> & A, Matrix<Scalar> & O) throw (DimensionException);
		template<class Matrix> static vector<unsigned int> whichmax(const Matrix & m);
		template<class Matrix> static vector<unsigned int> whichmin(const Matrix & m);
		template<class Matrix> static void print(const Matrix & m, ostream & out = cout);
		template<class Real> static void print(const vector<Real> & v, ostream & out = cout);
		template<class Matrix> static bool isSquare(const Matrix & A);
		template<class Scalar> static void inv(const Matrix<Scalar> & A, Matrix<Scalar> & O) throw (DimensionException);
		template<class MatrixA, class MatrixO> static void transpose(const MatrixA & A, MatrixO & O);
		template<class Scalar> static void kroneckerMult(const Matrix<Scalar> & A, const Matrix<Scalar> & B, Matrix<Scalar> & O);
		template<class Scalar> static void kroneckerSum(const Matrix<Scalar> & A, const Matrix<Scalar> & B, Matrix<Scalar> & O);
		template<class Scalar> static void kroneckerSum(const vector< Matrix<Scalar> *> & vA, Matrix<Scalar> & O);
};
