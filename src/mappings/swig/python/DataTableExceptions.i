%module bpp_
%{
#include "DataTableExceptions.h"
using namespace bpp;
%}
%include "Exceptions.i"
%include "TextTools.i"
%include "std_string.i"
using namespace std;

class TableNameNotFoundException:public Exception
{
	public:
		TableNameNotFoundException(const string & text, const string & name) :
			Exception("TableNameNotFoundException: " + name + ". " + text), _name(name);
		virtual ~TableNameNotFoundException() throw();

		string getName() const;		
};

class TableRowNameNotFoundException:public TableNameNotFoundException
{
	public:
		TableRowNameNotFoundException(const string & text, const string & name) : TableNameNotFoundException("TableRowNameNotFoundException: " + name + ". " + text, name);
		virtual ~TableRowNameNotFoundException() throw();
};

class TableColumnNameNotFoundException:public TableNameNotFoundException
{
	public:
		TableColumnNameNotFoundException(const string & text, const string & name) : TableNameNotFoundException("TableColumnNameNotFoundException: " + name + ". " + text, name);
		virtual ~TableColumnNameNotFoundException() throw();
};

class NoTableRowNamesException:public Exception
{
	public:
		NoTableRowNamesException(const string & text) : Exception("NoTableRowNamesException: "+text);
		virtual ~NoTableRowNamesException() throw();
};

class NoTableColumnNamesException:public Exception
{
	public:
		NoTableColumnNamesException(const string & text) : Exception("NoTableColumnNamesException: "+text);
		virtual ~NoTableColumnNamesException() throw();
};

class TableRowNamesException:public Exception
{
	public:
		TableRowNamesException(const string & text) : Exception("TableRowNamesException: "+text);
		virtual ~TableRowNamesException() throw();
};

class TableColumnNamesException:public Exception
{
	public:
		TableColumnNamesException(const string & text) : Exception("TableColumnNamesException: "+text);
		virtual ~TableColumnNamesException() throw();
};

class DuplicatedTableRowNameException:public Exception
{
	public:
		DuplicatedTableRowNameException(const string & text) : Exception("DuplicatedTableRowNameException: "+text);
		virtual ~DuplicatedTableRowNameException() throw();
};

class DuplicatedTableColumnNameException:public Exception
{
	public:
		DuplicatedTableColumnNameException(const string & text) : Exception("DuplicatedTableColumnNameException: "+text);
		virtual ~DuplicatedTableColumnNameException() throw();
};
