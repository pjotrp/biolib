%module bpptest
%{
#include "DarwinVarSingle.h"
using namespace bpp;
%}
%include "TextTools.i"
%include "FileTools.i"
%include "Exceptions.i"
%include "StringTokenizer.i"
%include "AbstractODataSet.i"

class DarwinVarSingle:public AbstractODataSet
{
  public: 
    DarwinVarSingle();
    ~DarwinVarSingle();

    void write(ostream & os, const DataSet & data_set) const throw (Exception);
    void write(const string & path, const DataSet & data_set, bool overwrite) const throw (Exception);
    virtual const string getFormatName();
    virtual const string getFormatDescription();
};
