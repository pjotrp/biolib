%module bpptest
%{
#include "DRTreeParsimonyScore.h"
using namespace bpp;
%}
%include "AbstractTreeParsimonyScore.i"
%include "NNISearchable.i"
%include "TreeTools.i"
%include "DRTreeParsimonyData.i"

%rename(__assign__) DRTreeParsimonyScore::operator=;

class DRTreeParsimonyScore:public virtual AbstractTreeParsimonyScore,public virtual NNISearchable
{
  public:
    DRTreeParsimonyScore(const Tree & tree,const SiteContainer & data,bool verbose = true)throw (Exception);
    DRTreeParsimonyScore(const DRTreeParsimonyScore & tp);
    DRTreeParsimonyScore& operator=(const DRTreeParsimonyScore & tp);
    virtual ~DRTreeParsimonyScore();
    DRTreeParsimonyScore * clone() const;

    unsigned int getScore() const;
    unsigned int getScoreForSite(unsigned int site) const;
    static void computeScoresPostorderForNode(const DRTreeParsimonyNodeData & pData, vector<Bitset> & rBitsets, vector<unsigned int> & rScores);
    static void computeScoresPreorderForNode(const DRTreeParsimonyNodeData & pData, const Node * source, vector<Bitset> & rBitsets, vector<unsigned int> & rScores);
    static void computeScoresForNode(const DRTreeParsimonyNodeData & pData, vector<Bitset> & rBitsets, vector<unsigned int> & rScores); 
    static void computeScoresFromArrays(const vector< const vector<Bitset> *> & iBitsets, const vector< const vector<unsigned int> *> & iScores, vector<Bitset> & oBitsets, vector<unsigned int> & oScores); 
    double getTopologyValue() const throw (Exception);
    double testNNI(int nodeId) const throw (NodeException);
    void doNNI(int nodeId) throw (NodeException);
    Tree * getTopology();
    const Tree * getTopology() const;
    void topologyChangeTested(const TopologyChangeEvent & event);
    void topologyChangeSuccessful(const TopologyChangeEvent & event);
};
