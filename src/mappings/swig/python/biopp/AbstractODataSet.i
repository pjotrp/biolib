%module bpptest
%{
#include "AbstractODataSet.h"
using namespace bpp;
%}
%include "ODataSet.i"

class AbstractODataSet:public ODataSet
{
  public:
    virtual ~AbstractODataSet();

    virtual void write(ostream & os, const DataSet & data_set) const throw (Exception) = 0;
    virtual void write(const string & path, const DataSet & data_set, bool overwrite) const throw (Exception);
};
