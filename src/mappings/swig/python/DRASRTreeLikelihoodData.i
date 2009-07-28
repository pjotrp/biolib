%module bpptest
%{
#include "DRASRTreeLikelihoodData.h"
using namespace bpp;
%}
%include "AbstractTreeLikelihoodData.i"
%include "SubstitutionModel.i"
%include "SitePatterns.i"
%include "VectorTools.i"
%include "std_map.i"
using namespace std;

class DRASRTreeLikelihoodNodeData :public TreeLikelihoodNodeData
{
  public:
    DRASRTreeLikelihoodNodeData* clone() const;

    const Node * getNode() const;
    void setNode(const Node & node);
    VVVdouble & getLikelihoodArray();
    const VVVdouble & getLikelihoodArray() const;
    VVVdouble & getDLikelihoodArray();
    const VVVdouble & getDLikelihoodArray() const;
    VVVdouble & getD2LikelihoodArray();
    const VVVdouble & getD2LikelihoodArray() const;
};

%rename(__assign__) DRASRTreeLikelihoodData::operator=;

class DRASRTreeLikelihoodData :public AbstractTreeLikelihoodData
{
  public:
    DRASRTreeLikelihoodData(TreeTemplate<Node> & tree, unsigned int nbClasses, bool usePatterns = true);
    DRASRTreeLikelihoodData(const DRASRTreeLikelihoodData & data);
    DRASRTreeLikelihoodData& operator=(const DRASRTreeLikelihoodData & data);
    virtual ~DRASRTreeLikelihoodData();
    DRASRTreeLikelihoodData* clone() const;

    void setTree(TreeTemplate<Node> & tree);
    DRASRTreeLikelihoodNodeData & getNodeData(int nodeId);
    const DRASRTreeLikelihoodNodeData & getNodeData(int nodeId) const;
    unsigned int getArrayPosition(int parentId, int sonId, unsigned int currentPosition) const;
    unsigned int getRootArrayPosition(unsigned int currentPosition) const;
    const vector<unsigned int> & getArrayPositions(int parentId, int sonId) const;
    vector<unsigned int> & getArrayPositions(int parentId, int sonId);
    unsigned int getArrayPosition(int parentId, int sonId, unsigned int currentPosition);
    VVVdouble & getLikelihoodArray(int nodeId);
    VVVdouble & getDLikelihoodArray(int nodeId);
    VVVdouble & getD2LikelihoodArray(int nodeId);
    unsigned int getNumberOfDistinctSites() const;
    unsigned int getNumberOfSites() const;
    unsigned int getNumberOfStates() const;
    unsigned int getNumberOfClasses() const;
    void initLikelihoods(const SiteContainer & sites, const SubstitutionModel & model) throw (Exception);
};
