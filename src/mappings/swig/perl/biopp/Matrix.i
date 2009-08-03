%module bpp_matrix
%{
#include "Matrix.h"
using namespace bpp;
%}
%include "std_vector.i"
using namespace std;
%include "Clonable.i"

%template(intVector) std::vector<int>;
%template(doubleVector) std::vector<double>;

%template(intVectorVector) std::vector< std::vector<int> >;
%template(doubleVectorVector) std::vector< std::vector<double> >;

template<class Scalar>
class Matrix:public Clonable
{
  public:
    Matrix();
    virtual ~Matrix();

    virtual const Scalar & operator()(unsigned int i, unsigned int j) const = 0;
    virtual Scalar & operator()(unsigned int i, unsigned int j) = 0;
    virtual const Scalar & operator()(int i, int j) const;
    virtual Scalar & operator()(int i, int j);
    virtual unsigned int nRows() const = 0;
    virtual unsigned int nCols() const = 0;
    virtual vector<Scalar> row(unsigned int i) const = 0;
    virtual vector<Scalar> col(unsigned int j) const = 0;
    virtual void resize(unsigned int nRows, unsigned int nCols) = 0;
};

%template(intMatrix) Matrix<int>;
%template(doubleMatrix) Matrix<double>;

%ignore *::operator=;

template<class Scalar>
class RowMatrix : public Matrix<Scalar>, public vector< vector<Scalar> > {
  public:
    RowMatrix();
    RowMatrix(unsigned int nRow, unsigned int nCol): vector< vector<Scalar> >(nRow);
    RowMatrix(const Matrix<Scalar> & m);
    virtual ~RowMatrix();

    RowMatrix<Scalar> & operator=(const Matrix<Scalar> & m);
    Clonable * clone() const;
    const Scalar & operator()(unsigned int i, unsigned int j) const;
    Scalar & operator()(unsigned int i, unsigned int j);
    unsigned int nRows() const;
    unsigned int nCols() const;
    vector<Scalar> row(unsigned int i) const;
    vector<Scalar> col(unsigned int j) const;
    void resize(unsigned int nRows, unsigned int nCols);
};

%template(intRowMatrix) RowMatrix<int>;
%template(doubleRowMatrix) RowMatrix<double>;
