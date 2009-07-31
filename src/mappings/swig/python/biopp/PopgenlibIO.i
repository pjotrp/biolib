%module bpptest
%{
#include "PopgenlibIO.h"
using namespace bpp;
%}
%include "TextTools.i"
%include "FileTools.i"
%include "Exceptions.i"
%include "Fasta.i"
%include "VectorSequenceContainer.i"
%include "AbstractIDataSet.i"
%include "AbstractODataSet.i"
%include "BasicAlleleInfo.i"

class PopgenlibIO:public AbstractIDataSet,public AbstractODataSet
{
  public: 
    static const string WHITESPACE;
    static const string TAB;
    static const string COMA;
    static const string SEMICOLON;
    static const string DIPLOID;
    static const string HAPLOID;
    static const string HAPLODIPLOID;
    static const string UNKNOWN;

    PopgenlibIO();
    PopgenlibIO(const string & missing_data_symbol, const string & data_separator) throw (Exception);
    ~PopgenlibIO();

    string getMissingDataSymbol() const;
    string getDataSeparator() const;
    char getMissingDataChar() const;
    char getDataSeparatorChar() const;
    void setMissingDataSymbol(const string & missing_data_symbol) throw (Exception);
    void setDataSeparator(const string & data_separator) throw (Exception);
    void read(istream & is, DataSet & data_set) throw (Exception);
    void read(const string & path, DataSet & data_set) throw (Exception);
    DataSet * read(istream & is) throw (Exception);
    DataSet * read(const string & path) throw (Exception);
    void write(ostream & os, const DataSet & data_set) const throw (Exception);
    void write(const string & path, const DataSet & data_set, bool overwrite) const throw (Exception);
    virtual const string getFormatName();
    virtual const string getFormatDescription();
};
