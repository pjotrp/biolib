%module bpptest
%{
#include "TreeTemplate.h"
using namespace bpp;
%}
%include "TreeExceptions.i"
%include "TreeTemplateTools.i"
%include "Tree.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
using namespace std;

%rename(__assign__) *::operator=;

template<class N> class TreeTemplate:public Tree
{
  public: 
    TreeTemplate();
    TreeTemplate(const TreeTemplate<N> & t);
    TreeTemplate(const Tree & t);
    TreeTemplate(N & root);
    TreeTemplate<N> & operator=(const TreeTemplate<N> & t);
    virtual ~TreeTemplate();
    TreeTemplate<N> * clone() const;

    string getName() const;
    void setName(const string & name);
    int getRootId() const;
    unsigned int getNumberOfLeaves() const;
    unsigned int getNumberOfNodes() const;
    int getLeafId(const string & name) const throw (NodeNotFoundException);
    vector<int> getLeavesId() const;
    vector<int> getNodesId() const;
    vector<double> getBranchLengths() const;
    vector<string> getLeavesNames() const;
    vector<int> getSonsId(int parentId) const throw (NodeNotFoundException)  ;
    int getFatherId(int parentId) const throw (NodeNotFoundException);
    bool hasFather(int nodeId) const throw (NodeNotFoundException);
    string getNodeName(int nodeId) const throw (NodeNotFoundException);
    bool hasNodeName(int nodeId) const throw (NodeNotFoundException);
    void setNodeName(int nodeId, const string & name) throw (NodeNotFoundException);
    void deleteNodeName(int nodeId) throw (NodeNotFoundException);
    bool hasNode(int nodeId) const;
    bool isLeaf(int nodeId) const throw (NodeNotFoundException);
    bool isRoot(int nodeId) const throw (NodeNotFoundException);
    double getDistanceToFather(int nodeId) const throw (NodeNotFoundException);
    void setDistanceToFather(int nodeId, double length) throw (NodeNotFoundException);
    void deleteDistanceToFather(int nodeId) throw (NodeNotFoundException);
    bool hasDistanceToFather(int nodeId) const throw (NodeNotFoundException);
    bool hasNodeProperty(int nodeId, const string & name) const throw (NodeNotFoundException);
    void setNodeProperty(int nodeId, const string & name, const Clonable & property) throw (NodeNotFoundException);
    Clonable * getNodeProperty(int nodeId, const string & name) throw (NodeNotFoundException);
    const Clonable * getNodeProperty(int nodeId, const string & name) const throw (NodeNotFoundException);
    Clonable * removeNodeProperty(int nodeId, const string & name) throw (NodeNotFoundException);
    vector<string> getNodePropertyNames(int nodeId) const throw (NodeNotFoundException);
    bool hasBranchProperty(int nodeId, const string & name) const throw (NodeNotFoundException);
    void setBranchProperty(int nodeId, const string & name, const Clonable & property) throw (NodeNotFoundException);
    Clonable * getBranchProperty(int nodeId, const string & name) throw (NodeNotFoundException);
    const Clonable * getBranchProperty(int nodeId, const string & name) const throw (NodeNotFoundException);
    Clonable * removeBranchProperty(int nodeId, const string & name) throw (NodeNotFoundException);
    vector<string> getBranchPropertyNames(int nodeId) const throw (NodeNotFoundException);
    void rootAt(int nodeId) throw (NodeNotFoundException)  ;
    void newOutGroup(int nodeId) throw (NodeNotFoundException);
    bool isRooted() const;
    bool unroot() throw (UnrootedTreeException);
    void resetNodesId();
    bool isMultifurcating() const;
    vector<double> getBranchLengths() throw (NodeException);
    double getTotalLength() throw (NodeException);
    void setBranchLengths(double brLen);
    void setVoidBranchLengths(double brLen);
    void scaleTree(double factor) throw (NodeException);
    int getNextId();
    void swapNodes(int parentId, unsigned int i1, unsigned int i2) throw (NodeNotFoundException,IndexOutOfBoundsException);
    virtual void setRootNode(N & root);
    virtual N * getRootNode();
    virtual const N * getRootNode() const;
    virtual vector<const N *> getLeaves() const;
    virtual vector<N *> getLeaves();
    virtual vector<const N *> getNodes() const;
    virtual vector<N *> getNodes();
    virtual vector<const N *> getInnerNodes() const;
    virtual vector<N *> getInnerNodes();
    virtual N * getNode(int id) throw (NodeNotFoundException, Exception);
    virtual const N * getNode(int id) const throw (NodeNotFoundException, Exception);
    virtual N * getNode(const string & name) throw (NodeNotFoundException, Exception);
    virtual const N * getNode(const string & name) const throw (NodeNotFoundException, Exception);
    void rootAt(N & newRoot);
    void newOutGroup(N & outGroup);
};

%template(intTreeTemplate) TreeTemplate<int>;
%template(doubleTreeTemplate) TreeTemplate<double>;
