%module bpp_
%{
#include "DataTable.h"
using namespace bpp;
%}
//%include "VectorTools.i"
%include "DataTableExceptions.i"
%include "Exceptions.i"
%include "TextTools.i"
%include "Clonable.i"
%include "std_string.i"
%include "std_map.i"
using namespace std;

%ignore DataTable::operator=;

class DataTable:public Clonable
{
  public:
    DataTable(unsigned int nRow, unsigned int nCol);
    DataTable(unsigned int nCol);
    DataTable(const vector<string> & colNames) throw (DuplicatedTableColumnNameException);
    DataTable(const DataTable & table);
    DataTable & operator=(const DataTable & table);
    DataTable * clone() const;
    virtual ~DataTable();

    string & operator()(unsigned int rowIndex, unsigned int colIndex) throw (IndexOutOfBoundsException);
    const string & operator()(unsigned int rowIndex, unsigned int colIndex) const throw (IndexOutOfBoundsException);
    string & operator()(const string & rowName, const string & colName)
            throw (NoTableRowNamesException, NoTableColumnNamesException, TableNameNotFoundException);
    const string & operator()(const string & rowName, const string & colName) const
            throw (NoTableRowNamesException, NoTableColumnNamesException, TableNameNotFoundException);
    string & operator()(const string & rowName, unsigned int colIndex)
            throw (NoTableRowNamesException, TableNameNotFoundException, IndexOutOfBoundsException);
    const string & operator()(const string & rowName, unsigned int colIndex) const
            throw (NoTableRowNamesException, TableNameNotFoundException, IndexOutOfBoundsException);
    string & operator()(unsigned int rowIndex, const string & colName)
            throw (IndexOutOfBoundsException, NoTableColumnNamesException, TableNameNotFoundException);
    const string & operator()(unsigned int rowIndex, const string & colName) const
            throw (IndexOutOfBoundsException, NoTableColumnNamesException, TableNameNotFoundException);
    unsigned int getNumberOfColumns() const;
    void setColumnNames(const vector<string> & colNames) throw (DimensionException, DuplicatedTableColumnNameException);
    vector<string> getColumnNames() const throw (NoTableColumnNamesException);
    string getColumnName(unsigned int index) const throw (NoTableColumnNamesException, IndexOutOfBoundsException);
    bool hasColumnNames() const;
    vector<string> & getColumn(unsigned int index) throw (IndexOutOfBoundsException);
    const vector<string> & getColumn(unsigned int index) const throw (IndexOutOfBoundsException);
    vector<string> & getColumn(const string & colName) throw (NoTableColumnNamesException, TableColumnNameNotFoundException);
    const vector<string> & getColumn(const string & colName) const throw (NoTableColumnNamesException, TableColumnNameNotFoundException);
    bool hasColumn(const string & colName) const;
    void deleteColumn(unsigned int index) throw (IndexOutOfBoundsException);
    void deleteColumn(const string & colName) throw (NoTableColumnNamesException, TableColumnNameNotFoundException);
    void addColumn(const vector<string> & newColumn) throw (DimensionException, TableColumnNamesException);
    void addColumn(const string & colName, const vector<string> & newColumn) throw (DimensionException, NoTableColumnNamesException, DuplicatedTableColumnNameException);
    unsigned int getNumberOfRows() const;
    void setRowNames(const vector<string> & rowNames) throw (DimensionException, DuplicatedTableRowNameException);
    vector<string> getRowNames() const throw (NoTableRowNamesException);
    bool hasRow(const string & rowName) const;
    string getRowName(unsigned int index) const throw (NoTableRowNamesException, IndexOutOfBoundsException);
    bool hasRowNames() const;
    vector<string> getRow(unsigned int index) const throw (IndexOutOfBoundsException);
    vector<string> getRow(const string & rowName) const throw (NoTableRowNamesException, TableRowNameNotFoundException);
    void deleteRow(unsigned int index) throw (IndexOutOfBoundsException);
    void deleteRow(const string & rowName) throw (NoTableRowNamesException, TableRowNameNotFoundException);
    void addRow(const vector<string> & newRow) throw (DimensionException, TableRowNamesException);
    void addRow(const string & rowName, const vector<string> & newRow) throw (DimensionException, NoTableRowNamesException, DuplicatedTableRowNameException);

    static DataTable * read(istream & in, const string & sep = "\t", bool header=true, int rowNames=-1)
      throw (DimensionException, IndexOutOfBoundsException, DuplicatedTableRowNameException);
    static void write(const DataTable & data, ostream & out, const string & sep = "\t");
};
