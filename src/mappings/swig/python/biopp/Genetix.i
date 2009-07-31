%module bpptest
%{
#include "Genetix.h"
using namespace bpp;
%}
%include "TextTools.i"
%include "FileTools.i"
%include "Exceptions.i"
%include "StringTokenizer.i"
%include "AbstractIDataSet.i"
%include "BasicAlleleInfo.i"

class Genetix:public AbstractIDataSet
{
  public: 
    Genetix();
    ~Genetix();

    void read(istream & is, DataSet & data_set) throw (Exception);
    void read(const string & path, DataSet & data_set) throw (Exception);
    DataSet * read(istream & is) throw (Exception);
    DataSet * read(const string & path) throw (Exception);
    virtual const string getFormatName();
    virtual const string getFormatDescription();
};
