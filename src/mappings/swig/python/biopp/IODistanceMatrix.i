%module bpptest
%{
#include "IODistanceMatrix.h"
using namespace bpp;
%}
%include "IOFormat.i"
%include "std_iostream.i"
//#include <fstream>
using namespace std;

%ignore IODistanceMatrix::IODistanceMatrix;
%ignore IODistanceMatrix::~IODistanceMatrix;

class DistanceMatrix;
class IODistanceMatrix:public virtual IOFormat
{
	public:
		IODistanceMatrix();
		virtual ~IODistanceMatrix();

		virtual const string getDataType() const;
};

%ignore IDistanceMatrix::IDistanceMatrix;
%ignore IDistanceMatrix::~IDistanceMatrix;

class IDistanceMatrix:public virtual IODistanceMatrix
{
	public:
		IDistanceMatrix();
		virtual ~IDistanceMatrix();

		virtual DistanceMatrix * read(const string & path) const throw (Exception) = 0;
		virtual DistanceMatrix * read(istream & in) const throw (Exception) = 0;
};

%ignore ODistanceMatrix::ODistanceMatrix;
%ignore ODistanceMatrix::~ODistanceMatrix;

class ODistanceMatrix:public virtual IODistanceMatrix
{
	public:
		ODistanceMatrix();
		virtual ~ODistanceMatrix();

		virtual void write(const DistanceMatrix & dist, const string & path, bool overwrite) const throw (Exception) = 0;
		virtual void write(const DistanceMatrix & dist, ostream & out) const throw (Exception) = 0;
};

class AbstractIDistanceMatrix:public virtual IDistanceMatrix
{
	public:
		AbstractIDistanceMatrix();
		virtual ~AbstractIDistanceMatrix();

		virtual DistanceMatrix * read(const string & path) const throw (Exception);
		virtual DistanceMatrix * read(istream & in) const throw (Exception) = 0;
};

class AbstractODistanceMatrix:public virtual ODistanceMatrix
{
	public:
		AbstractODistanceMatrix();
		virtual ~AbstractODistanceMatrix();

		virtual void write(const DistanceMatrix & dist, const string & path, bool overwrite) const throw (Exception);
		virtual void write(const DistanceMatrix & dist, ostream & out) const throw (Exception) = 0;
};
