%module bpptest
%{
#include "AbstractIDataSet.h"
using namespace bpp;
%}
%include "IDataSet.i"
%include "Exceptions.i"

class AbstractIDataSet:public IDataSet
{
  public: 
    virtual ~AbstractIDataSet();

    virtual void read(istream & is, DataSet & data_set) throw (Exception) = 0;
    virtual void read(const string & path, DataSet & data_set) throw (Exception);
    virtual DataSet * read(istream & is) throw (Exception);
    virtual DataSet * read(const string & path) throw (Exception);
};
