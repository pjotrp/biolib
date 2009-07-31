%module bpptest
%{
#include "Tree.h"
using namespace bpp;
%}
%include "TreeExceptions.i"
%include "Clonable.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
using namespace std;

%ignore Tree::Tree;
%ignore Tree::~Tree;
%ignore Tree::swapNodes;

class Tree:public Clonable
{
  public: 
    Tree();
    virtual ~Tree();
    Tree * clone() const = 0;

    virtual string getName() const = 0;
    virtual void setName(const string & name) = 0;
    virtual unsigned int getNumberOfLeaves() const = 0;
    virtual unsigned int getNumberOfNodes() const = 0;
    virtual vector<double> getBranchLengths() const = 0;
    virtual vector<string> getLeavesNames() const = 0;
    virtual int getRootId() const = 0;
    virtual int getLeafId(const string & name) const throw (NodeNotFoundException)= 0;
    virtual vector<int> getLeavesId() const = 0;
    virtual vector<int> getNodesId() const = 0;
    virtual vector<int> getSonsId(int parentId) const throw (NodeNotFoundException) = 0;
    virtual int getFatherId(int parentId) const throw (NodeNotFoundException) = 0;
    virtual bool hasFather(int nodeId) const throw (NodeNotFoundException) = 0;
    virtual string getNodeName(int nodeId) const throw (NodeNotFoundException) = 0;
    virtual void setNodeName(int nodeId, const string & name) throw (NodeNotFoundException) = 0;
    virtual void deleteNodeName(int nodeId) throw (NodeNotFoundException) = 0;
    virtual bool hasNodeName(int nodeId) const throw (NodeNotFoundException) = 0;
    virtual bool hasNode(int nodeId) const = 0;
    virtual bool isLeaf(int nodeId) const throw (NodeNotFoundException) = 0;
    virtual bool isRoot(int nodeId) const throw (NodeNotFoundException) = 0;
    void swapNodes(const Tree & tree, int nodeId, unsigned int i1=0, unsigned int i2=1) throw (NodeNotFoundException,IndexOutOfBoundsException);
    virtual double getDistanceToFather(int nodeId) const throw (NodeNotFoundException) = 0;
    virtual void setDistanceToFather(int nodeId, double length) throw (NodeNotFoundException) = 0;
    virtual void deleteDistanceToFather(int nodeId) throw (NodeNotFoundException) = 0;
    virtual bool hasDistanceToFather(int nodeId) const throw (NodeNotFoundException) = 0;
    virtual bool hasNodeProperty(int nodeId, const string & name) const throw (NodeNotFoundException) = 0;
    virtual void setNodeProperty(int nodeId, const string & name, const Clonable & property) throw (NodeNotFoundException) = 0;
    virtual Clonable * getNodeProperty(int nodeId, const string & name) throw (NodeNotFoundException) = 0;
    virtual const Clonable * getNodeProperty(int nodeId, const string & name) const throw (NodeNotFoundException) = 0;
    virtual Clonable * removeNodeProperty(int nodeId, const string & name) throw (NodeNotFoundException) = 0;
    virtual vector<string> getNodePropertyNames(int nodeId) const throw (NodeNotFoundException) = 0;
    virtual bool hasBranchProperty(int nodeId, const string & name) const throw (NodeNotFoundException) = 0;
    virtual void setBranchProperty(int nodeId, const string & name, const Clonable & property) throw (NodeNotFoundException) = 0;
    virtual Clonable * getBranchProperty(int nodeId, const string & name) throw (NodeNotFoundException) = 0;
    virtual const Clonable * getBranchProperty(int nodeId, const string & name) const throw (NodeNotFoundException) = 0;
    virtual Clonable * removeBranchProperty(int nodeId, const string & name) throw (NodeNotFoundException) = 0;
    virtual vector<string> getBranchPropertyNames(int nodeId) const throw (NodeNotFoundException) = 0;
    virtual void rootAt(int nodeId) throw (NodeNotFoundException) = 0;
    virtual void newOutGroup(int nodeId) throw (NodeNotFoundException) = 0;
    virtual bool isRooted() const = 0;
    virtual bool unroot() throw (UnrootedTreeException) = 0;
    virtual void resetNodesId() = 0;
    virtual bool isMultifurcating() const = 0;
    virtual vector<double> getBranchLengths() throw (NodeException) = 0;
    virtual double getTotalLength() throw (NodeException) = 0;
    virtual void setBranchLengths(double brLen) = 0;
    virtual void setVoidBranchLengths(double brLen) = 0;
    virtual void scaleTree(double factor) throw (NodeException) = 0;
    virtual int getNextId() = 0;
};
