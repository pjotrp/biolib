%module bpptest
%{
#include "DRASDRTreeLikelihoodData.h"
using namespace bpp;
%}
%include "AbstractTreeLikelihoodData.i"
%include "SubstitutionModel.i"
%include "PatternTools.i"
%include "SitePatterns.i"
%include "AlignedSequenceContainer.i"
%include "std_map.i"
using namespace std;

class DRASDRTreeLikelihoodLeafData :public TreeLikelihoodNodeData
{
  public:
    DRASDRTreeLikelihoodLeafData* clone() const;

    const Node * getNode() const;
    void setNode(const Node & node);
    VVdouble & getLikelihoodArray();
};

class DRASDRTreeLikelihoodNodeData :public TreeLikelihoodNodeData
{
  public:
    DRASDRTreeLikelihoodNodeData* clone() const;

    const Node * getNode() const;
    void setNode(const Node & node);
    const map<int, VVVdouble> & getLikelihoodArrays() const;
    map<int, VVVdouble> & getLikelihoodArrays();
    VVVdouble & getLikelihoodArrayForNeighbor(int neighborId);
    const VVVdouble & getLikelihoodArrayForNeighbor(int neighborId) const;
    Vdouble & getDLikelihoodArray();
    const Vdouble & getDLikelihoodArray() const;
    Vdouble & getD2LikelihoodArray();
    const Vdouble & getD2LikelihoodArrayForNeighbor() const;
    bool isNeighbor(int neighborId) const;
    void eraseNeighborArrays();
};

%rename(__assign__) DRASDRTreeLikelihoodData::operator=;

class DRASDRTreeLikelihoodData : public AbstractTreeLikelihoodData
{
  public:
    DRASDRTreeLikelihoodData(TreeTemplate<Node> & tree, unsigned int nbClasses);
    DRASDRTreeLikelihoodData(const DRASDRTreeLikelihoodData & data);
    DRASDRTreeLikelihoodData & operator=(const DRASDRTreeLikelihoodData & data);
    virtual ~DRASDRTreeLikelihoodData();

    DRASDRTreeLikelihoodData* clone() const;

    void setTree(TreeTemplate<Node> & tree);
    DRASDRTreeLikelihoodNodeData & getNodeData(int nodeId);
    const DRASDRTreeLikelihoodNodeData & getNodeData(int nodeId) const;
    DRASDRTreeLikelihoodLeafData & getLeafData(int nodeId);
    const DRASDRTreeLikelihoodLeafData & getLeafData(int nodeId) const;
    unsigned int getArrayPosition(int parentId, int sonId, unsigned int currentPosition) const;
    const map<int, VVVdouble> & getLikelihoodArrays(int nodeId) const;
    map<int, VVVdouble> & getLikelihoodArrays(int nodeId);
    VVVdouble & getLikelihoodArray(int parentId, int neighborId);
    const VVVdouble & getLikelihoodArray(int parentId, int neighborId) const;
    Vdouble & getDLikelihoodArray(int nodeId);
    const Vdouble & getDLikelihoodArray(int nodeId) const;
    Vdouble & getD2LikelihoodArray(int nodeId);
    const Vdouble & getD2LikelihoodArray(int nodeId) const;
    VVdouble & getLeafLikelihoods(int nodeId);
    const VVdouble & getLeafLikelihoods(int nodeId) const;
    VVVdouble & getRootLikelihoodArray();
    const VVVdouble & getRootLikelihoodArray() const;
    VVdouble  & getRootSiteLikelihoodArray();
    const VVdouble  & getRootSiteLikelihoodArray() const;
    Vdouble   & getRootRateSiteLikelihoodArray();
    const Vdouble   & getRootRateSiteLikelihoodArray() const;
    unsigned int getNumberOfDistinctSites() const;
    unsigned int getNumberOfSites() const;
    unsigned int getNumberOfStates() const;
    unsigned int getNumberOfClasses() const;
    const SiteContainer * getShrunkData() const;
    void initLikelihoods(const SiteContainer & sites, const SubstitutionModel & model) throw (Exception);
    void reInit() throw (Exception);
    void reInit(const Node * node) throw (Exception);
};
