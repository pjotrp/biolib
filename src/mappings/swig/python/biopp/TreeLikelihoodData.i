%module bpptest
%{
#include "TreeLikelihoodData.h"
using namespace bpp;
%}
%include "Node.i"
%include "TreeTemplate.i"
%include "Alphabet.i"
%include "SiteContainer.i"

class TreeLikelihoodNodeData:public virtual Clonable
{
  public:
    TreeLikelihoodNodeData();
    virtual ~TreeLikelihoodNodeData();
    TreeLikelihoodNodeData* clone() const = 0;

    virtual const Node * getNode() const = 0;
    virtual void setNode(const Node & node) = 0;
};

class TreeLikelihoodData:public virtual Clonable
{
  public:
    TreeLikelihoodData();
    virtual ~TreeLikelihoodData();
    TreeLikelihoodData * clone() const = 0;

    virtual const Alphabet * getAlphabet() const = 0;
    virtual const TreeTemplate<Node> * getTree() const = 0;
    virtual TreeTemplate<Node> * getTree() = 0;
    virtual void setTree(TreeTemplate<Node> & tree) = 0;
    virtual unsigned int getArrayPosition(int parentId, int sonId, unsigned int currentPosition) const = 0;
    virtual unsigned int getRootArrayPosition(const unsigned int site) const = 0;
    virtual       TreeLikelihoodNodeData & getNodeData(int nodeId) = 0;
    virtual const TreeLikelihoodNodeData & getNodeData(int nodeId) const = 0;
};
