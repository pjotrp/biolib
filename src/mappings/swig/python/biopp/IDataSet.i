%module bpptest
%{
#include "IDataSet.h"
using namespace bpp;
%}
%include "IODataSet.i"
%include "Exceptions.i"

%ignore IDataSet::IDataSet;
%ignore IDataSet::~IDataSet;

class IDataSet:public virtual IODataSet
{
  public: 
    virtual ~IDataSet();

    virtual void read(istream & is, DataSet & data_set) throw (Exception) = 0;
    virtual void read(const string & path, DataSet & data_set) throw (Exception) = 0;
    virtual DataSet * read(istream & is) throw (Exception) = 0;
    virtual DataSet * read(const string & path) throw (Exception) = 0;
};
