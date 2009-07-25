%module bpptest
%{
#include "DistanceMatrix.h"
using namespace bpp;
%}
%include "std_vector.i"
%include "std_string.i"
using namespace std;
%include "Exceptions.i"
%include "VectorExceptions.i" 
%include "Matrix.i"

%rename(__assign__) DistanceMatrix::operator=;

class DistanceMatrix:public virtual RowMatrix<double>
{
  public:
    DistanceMatrix(const vector<string> & names): RowMatrix<double>(names.size(), names.size()), _names(names);
    DistanceMatrix(unsigned int n): RowMatrix<double>(n, n), _names(n);
    virtual ~DistanceMatrix();
    DistanceMatrix(const DistanceMatrix & dist): RowMatrix<double>(dist), _names(dist._names);
    DistanceMatrix & operator=(const DistanceMatrix & dist);

    void reset();
    unsigned int size() const;
    vector<string> getNames() const;
    string getName(unsigned int i) const throw (IndexOutOfBoundsException);
    void setName(unsigned int i, const string & name) throw (IndexOutOfBoundsException);
    void setNames(const vector<string> & names) throw (DimensionException);
    unsigned int getNameIndex(const string & name) const throw (Exception);
    virtual const double & operator()(const string & iName, const string & jName) const throw (Exception);
    virtual double & operator()(const string & iName, const string & jName) throw (Exception);
    virtual const double & operator()(unsigned int i, unsigned int j) const;
    virtual double & operator()(unsigned int i, unsigned int j);
    virtual const double & operator()(int i, int j) const;
    virtual double & operator()(int i, int j);
};
