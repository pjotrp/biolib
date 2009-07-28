%module bpptest
%{
#include "AbstractTreeLikelihoodData.h"
using namespace bpp;
%}
%include "TreeLikelihoodData.i"
%include "std_vector.i"
%include "std_map.i"
using namespace std;

class AbstractTreeLikelihoodData :public TreeLikelihoodData
{
  public:
    AbstractTreeLikelihoodData();
    virtual ~AbstractTreeLikelihoodData();

    vector<unsigned int> & getRootArrayPositions();
    const vector<unsigned int> & getRootArrayPositions() const;
    unsigned int getRootArrayPosition(const unsigned int site) const;
    unsigned int getWeight(unsigned int pos) const;
    const vector<unsigned int> & getWeights() const;
    const Alphabet * getAlphabet() const;
    const TreeTemplate<Node> * getTree() const;  
    TreeTemplate<Node> * getTree();
};
