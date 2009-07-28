%module bpptest
%{
#include "AbstractTreeParsimonyData.h"
using namespace bpp;
%}
%include "TreeParsimonyData.i"

class AbstractTreeParsimonyData:public TreeParsimonyData
{
  public:
    AbstractTreeParsimonyData();
    virtual ~AbstractTreeParsimonyData();

    unsigned int getRootArrayPosition(const unsigned int site) const;
    unsigned int getWeight(unsigned int pos) const;
    const TreeTemplate<Node> * getTree() const;  
    TreeTemplate<Node> * getTree();
};
