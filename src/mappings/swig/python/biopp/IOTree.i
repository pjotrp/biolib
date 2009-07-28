%module bpptest
%{
#include "IOTree.h"
using namespace bpp;
%}
%include "Tree.i"
%include "std_string.i"
%include "std_iostream.i"
#include <fstream>
using namespace std;
%include "Exceptions.i"
%include "IOFormat.i"

class IOTree:public virtual IOFormat
{
  public:
    IOTree();
    virtual ~IOTree();

    virtual const string getDataType() const;
};

class ITree:public virtual IOTree
{
  public:
    ITree();
    virtual ~ITree();

    virtual Tree * read(const string & path) const throw (Exception) = 0;
    virtual Tree * read(istream & in) const throw (Exception) = 0;
};

class OTree:public virtual IOTree
{
  public:
    OTree();
    virtual ~OTree();

    virtual void write(const Tree & tree, const string & path, bool overwrite) const throw (Exception) = 0;
    virtual void write(const Tree & tree, ostream & out) const throw (Exception) = 0;
};

class AbstractITree:public virtual ITree
{
  public:
    AbstractITree();
    virtual ~AbstractITree();

    virtual Tree * read(istream & in) const throw (Exception) = 0;
    virtual Tree * read(const string & path) const throw (Exception);
};

class AbstractOTree:public virtual OTree
{
  public:
    AbstractOTree();
    virtual ~AbstractOTree();

    void write(const Tree & tree, ostream & out) const throw (Exception) = 0;
    virtual void write(const Tree & tree, const string & path, bool overwrite) const throw (Exception);
};

class IMultiTree:public virtual IOTree
{
  public:
    IMultiTree();
    virtual ~IMultiTree();

    virtual void read(const string & path, vector<Tree *> & trees) const throw (Exception) = 0;
    virtual void read(istream & in, vector<Tree *> & trees) const throw (Exception) = 0;
};

class OMultiTree:public virtual IOTree
{
  public:
    OMultiTree();
    virtual ~OMultiTree();
  public:
    virtual void write(const vector<Tree *> & trees, const string & path, bool overwrite) const throw (Exception) = 0;
    virtual void write(const vector<Tree *> & trees, ostream & out) const throw (Exception) = 0;
};

class AbstractIMultiTree:public virtual IMultiTree
{
  public:
    AbstractIMultiTree();
    virtual ~AbstractIMultiTree();
  public:
    virtual void read(istream & in, vector<Tree *> & trees) const throw (Exception) = 0;
    virtual void read(const string & path, vector<Tree *> & trees) const throw (Exception);
};

class AbstractOMultiTree:public virtual OMultiTree
{
  public:
    AbstractOMultiTree();
    virtual ~AbstractOMultiTree();

    void write(const vector<Tree *> & trees, ostream & out) const throw (Exception) = 0;
    virtual void write(const vector<Tree *> & trees, const string & path, bool overwrite) const throw (Exception);
};
