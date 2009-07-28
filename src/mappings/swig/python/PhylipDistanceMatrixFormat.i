%module bpptest
%{
#include "PhylipDistanceMatrixFormat.h"
using namespace bpp;
%}
%include "IODistanceMatrix.i"

class PhylipDistanceMatrixFormat:public virtual AbstractIDistanceMatrix,public virtual AbstractODistanceMatrix
{
  public:
    PhylipDistanceMatrixFormat();
    virtual ~PhylipDistanceMatrixFormat();

    const string getFormatName() const;
    const string getFormatDescription() const;
    DistanceMatrix * read(const string & path) const throw (Exception);
    DistanceMatrix * read(istream & in) const throw (Exception);
    void write(const DistanceMatrix & dist, const string & path, bool overwrite = true) const throw (Exception);
    void write(const DistanceMatrix & dist, ostream & out) const throw (Exception);
};
