%module bpptest
%{
#include "ODataSet.h"
using namespace bpp;
%}
%include "IODataSet.i"
%include "Exceptions.i"

%ignore ODataSet::ODataSet;
%ignore ODataSet::~ODataSet;

class ODataSet:public virtual IODataSet
{
  public: 
    virtual ~ODataSet();

    virtual void write(ostream & os, const DataSet & data_set) const throw (Exception) = 0;
    virtual void write(const string & path, const DataSet & data_set, bool overwrite) const throw (Exception) = 0;
};
