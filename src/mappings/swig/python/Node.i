%module bpptest
%{
#include "Node.h"
using namespace bpp;
%}
%include "TreeExceptions.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
%include "std_iostream.i"
using namespace std;
%include "Clonable.i"
%include "MapTools.i"
//%include "BppString.i"
%include "Number.i"

%rename(__assign__) Node::operator=;
%rename(__aref__) Node::operator[];
%rename(__eq__) Node::operator==;

class Node:public Clonable
{
  public:
    Node();
    Node(int id);
    Node(const string & name);
    Node(int id, const string & name);
    Node(const Node & node);
    Node & operator=(const Node & node);
    virtual ~Node();
    Node * clone() const;

    virtual int getId() const;
    virtual void setId(int id);
    virtual vector<int> getSonsId() const;
    virtual string getName() const throw (NodeException);
    virtual void setName(const string & name);
    virtual void deleteName();
    virtual bool hasName() const;
    virtual double getDistanceToFather() const throw (NodeException) ;
    virtual void setDistanceToFather(double distance);
    virtual void deleteDistanceToFather();
    virtual bool hasDistanceToFather() const;
    virtual const Node * getFather() const;
    virtual Node * getFather();
    virtual int getFatherId() const;
    virtual void setFather(Node & node);
    virtual Node * removeFather();
    virtual bool hasFather() const;
    virtual unsigned int getNumberOfSons() const;
    virtual vector<Node *>& getSons();
    virtual const Node * getSon(unsigned int pos) const throw (IndexOutOfBoundsException);
    virtual Node * getSon(unsigned int pos) throw (IndexOutOfBoundsException);
    virtual void addSon(unsigned int pos, Node & node);
    virtual void addSon(Node & node);
    virtual void setSon(unsigned int pos, Node & node) throw (IndexOutOfBoundsException);
    virtual Node * removeSon(unsigned int pos) throw (IndexOutOfBoundsException);
    virtual void removeSon(Node & node) throw (NodeNotFoundException);
    virtual void removeSons();
    virtual void swap(unsigned int branch1, unsigned int branch2) throw (IndexOutOfBoundsException);
    virtual unsigned int getSonPosition(const Node & son) const throw (NodeNotFoundException);
    vector<const Node *> getNeighbors() const;
    vector<Node *> getNeighbors();
    virtual unsigned int degree() const;
    Node * operator[](int i);
    const Node * operator[](int i) const;
    virtual void setNodeProperty(const string & name, const Clonable & property);
    virtual Clonable * getNodeProperty(const string & name) throw (PropertyNotFoundException);
    virtual const Clonable * getNodeProperty(const string & name) const throw (PropertyNotFoundException);
    virtual Clonable * removeNodeProperty(const string & name) throw (PropertyNotFoundException);
    virtual void deleteNodeProperty(const string & name) throw (PropertyNotFoundException);
    virtual void removeNodeProperties();
    virtual void deleteNodeProperties();
    virtual bool hasNodeProperty(const string & name) const;
    virtual vector<string> getNodePropertyNames() const;
    virtual void setBranchProperty(const string & name, const Clonable & property);
    virtual Clonable * getBranchProperty(const string & name) throw (PropertyNotFoundException);
    virtual const Clonable * getBranchProperty(const string & name) const throw (PropertyNotFoundException);
    virtual Clonable * removeBranchProperty(const string & name) throw (PropertyNotFoundException);
    virtual void deleteBranchProperty(const string & name) throw (PropertyNotFoundException);
    virtual void removeBranchProperties();
    virtual void deleteBranchProperties();
    virtual bool hasBranchProperty(const string & name) const;
    virtual vector<string> getBranchPropertyNames() const;
    virtual double getBootstrapValue() const throw (PropertyNotFoundException);
    virtual bool operator==(const Node & node) const;  
    virtual bool isLeaf() const;
};
