%module bpp_
%{
#include "LUDecomposition.h"
%}
%include "Matrix.i"
%include "MatrixTools.i"
%include "NumTools.i"
//#include <algorithm>
using namespace std;
namespace bpp
{
template <class Real>
class LUDecomposition
{
  RowMatrix<Real>  LU;
  unsigned int m, n;
	int pivsign; 
  vector<unsigned int> piv;
	private:
		static RowMatrix<Real> permuteCopy(const Matrix<Real> &A, const vector<unsigned int> &piv, unsigned int j0, unsigned int j1);
	  static vector<Real> permuteCopy(const vector<Real> &A, const vector<unsigned int> &piv);
 		
	  LUDecomposition (const Matrix<Real> &A) : LU(A), m(A.nRows()), n(A.nCols()), piv(A.nRows());
    bool isNonsingular () const;
  	RowMatrix<Real> getL () const;
    vector<Real> solve (const vector<Real> &b) const;
}; 
} 
