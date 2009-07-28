%module bpptest
%{
#include "TreeExceptions.h"
using namespace bpp;
%}
%include "Exceptions.i"
%include "std_string.i"
using namespace std;

class Node;
class Tree;
class NodeException:public Exception
{
  public:
    NodeException(const string & text, const Node * node = NULL);
    NodeException(const string & text, int nodeId);
    virtual ~NodeException() throw ();

    virtual const Node * getNode() const;
    virtual int getNodeId() const;
};

class PropertyNotFoundException:public NodeException
{
  public:
    PropertyNotFoundException(const string & text, const string & propertyName, const Node * node = NULL);
    PropertyNotFoundException(const string & text, const string & propertyName, int nodeId);
    virtual ~PropertyNotFoundException() throw ();

    virtual const string & getPropertyName() const;
};

class NodeNotFoundException:public Exception
{
  public:
    NodeNotFoundException(const string & text, const string & id);
    NodeNotFoundException(const string & text, int id);
    virtual ~NodeNotFoundException() throw ();

    virtual string getId() const;
};

class TreeException:public Exception
{
  public:
    TreeException(const string & text, const Tree * tree = NULL);
    virtual ~TreeException() throw ();

    virtual const Tree * getTree() const;
};

class UnrootedTreeException:public TreeException
{
  public:
    UnrootedTreeException(const string & text, const Tree * tree = NULL);
    virtual ~UnrootedTreeException() throw ();
};
