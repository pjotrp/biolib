%module bpptest
%{
#include "GeneMapperCsvExport.h"
using namespace bpp;
%}
%include "TextTools.i"
%include "FileTools.i"
%include "Exceptions.i"
%include "StringTokenizer.i"
%include "DataTable.i"
%include "AbstractIDataSet.i"
%include "BasicAlleleInfo.i"
%include "MultiAlleleMonolocusGenotype.i"

class GeneMapperCsvExport: public AbstractIDataSet
{
  public: 
    GeneMapperCsvExport(bool ia = false);
    ~GeneMapperCsvExport();

    void read(istream & is, DataSet & data_set) throw (Exception);
    void read(const string & path, DataSet & data_set) throw (Exception);
    DataSet * read(istream & is) throw (Exception);
    DataSet * read(const string & path) throw (Exception);
    virtual const string getFormatName();
    virtual const string getFormatDescription();
};
