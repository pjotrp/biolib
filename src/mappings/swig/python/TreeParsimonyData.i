%module bpptest
%{
#include "TreeParsimonyData.h"
using namespace bpp;
%}
%include "Node.i"
%include "TreeTemplate.i"
%include "Clonable.i"

class TreeParsimonyNodeData:public virtual Clonable
{
  public:
    TreeParsimonyNodeData();
    virtual ~TreeParsimonyNodeData();
    TreeParsimonyNodeData * clone() const = 0;
    virtual const Node * getNode() const = 0;
    virtual void setNode(const Node & node) = 0;
};

class TreeParsimonyData:public virtual Clonable
{
  public:
    TreeParsimonyData();
    virtual ~TreeParsimonyData();
    TreeParsimonyData * clone() const = 0;

    virtual const TreeTemplate<Node> * getTree() const = 0;  
    virtual TreeTemplate<Node> * getTree() = 0;
    virtual unsigned int getArrayPosition(int parentId, int sonId, unsigned int currentPosition) const = 0;
    virtual unsigned int getRootArrayPosition(const unsigned int site) const = 0;
    virtual TreeParsimonyNodeData & getNodeData(int nodeId) = 0;
    virtual const TreeParsimonyNodeData & getNodeData(int nodeId) const = 0;
};
