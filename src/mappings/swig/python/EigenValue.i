%module bpp_
%{
#include "EigenValue.h"
%}
#include <algorithm>
#include <cmath>
using namespace std;
%include "Matrix.i"
%include "NumTools.i"
namespace bpp
{
template <class Real>
class EigenValue
{
  public:
    EigenValue(const Matrix<Real> &A);
    const RowMatrix<Real> & getV() const;
    const vector<Real> & getRealEigenValues() const;
    const vector<Real> & getImagEigenValues() const;
    const RowMatrix<Real>& getD() const;
};
} 
