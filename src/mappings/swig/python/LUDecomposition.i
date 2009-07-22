%module bpp_
%{
#include "LUDecomposition.h"
using namespace bpp;
%}
%include "Matrix.i"
//%include "MatrixTools.i"
//%include "NumTools.i"
//#include <algorithm>
using namespace std;

template <class Real>
class LUDecomposition
{
    LUDecomposition (const Matrix<Real> &A) : LU(A), m(A.nRows()), n(A.nCols()), piv(A.nRows());
    bool isNonsingular () const;
    RowMatrix<Real> getL () const;
    vector<Real> solve (const vector<Real> &b) const;
}; 
