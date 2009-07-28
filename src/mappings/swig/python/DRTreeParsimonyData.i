%module bpptest
%{
#include "DRTreeParsimonyData.h"
using namespace bpp;
%}
%include "AbstractTreeParsimonyData.i"
%include "SiteContainer.i"
#include <bitset>
using namespace std;

typedef bitset<20> Bitset;
class DRTreeParsimonyNodeData :public TreeParsimonyNodeData
{
  public:
    DRTreeParsimonyNodeData* clone() const;

    const Node * getNode() const;
    void setNode(const Node & node);
    vector<Bitset> & getBitsetsArrayForNeighbor(int neighborId);
    const vector<Bitset> & getBitsetsArrayForNeighbor(int neighborId) const;
    vector<unsigned int> & getScoresArrayForNeighbor(int neighborId);
    const vector<unsigned int> & getScoresArrayForNeighbor(int neighborId) const;
    bool isNeighbor(int neighborId) const;
    void eraseNeighborArrays();
};

class DRTreeParsimonyLeafData :public TreeParsimonyNodeData
{
  public:
    DRTreeParsimonyLeafData* clone() const;

    const Node * getNode() const;
    void setNode(const Node & node);
    vector<Bitset> & getBitsetsArray();
    const vector<Bitset> & getBitsetsArray() const;
};

%rename(__assign__) DRTreeParsimonyData::operator=;

class DRTreeParsimonyData :public AbstractTreeParsimonyData
{
  public:
    DRTreeParsimonyData(TreeTemplate<Node> & tree);
    DRTreeParsimonyData(const DRTreeParsimonyData & data);
    DRTreeParsimonyData & operator=(const DRTreeParsimonyData & data);
    virtual ~DRTreeParsimonyData();
    DRTreeParsimonyData* clone() const;

    void setTree(TreeTemplate<Node> & tree);
    DRTreeParsimonyNodeData & getNodeData(int nodeId);
    const DRTreeParsimonyNodeData & getNodeData(int nodeId) const;
    DRTreeParsimonyLeafData & getLeafData(int nodeId);
    const DRTreeParsimonyLeafData & getLeafData(int nodeId) const;
    vector<Bitset> & getBitsetsArray(int nodeId, int neighborId);
    const vector<Bitset> & getBitsetsArray(int nodeId, int neighborId) const;
    vector<unsigned int> & getScoresArray(int nodeId, int neighborId);
    const vector<unsigned int> & getScoresArray(int nodeId, int neighborId) const;
    unsigned int getArrayPosition(int parentId, int sonId, unsigned int currentPosition) const;
    vector<Bitset> & getRootBitsets();
    const vector<Bitset> & getRootBitsets() const;
    const Bitset & getRootBitset(unsigned int i) const;
    vector<unsigned int> & getRootScores();
    const vector<unsigned int> & getRootScores() const;
    unsigned int getRootScore(unsigned int i) const;
    unsigned int getNumberOfDistinctSites() const;
    unsigned int getNumberOfSites() const;
    unsigned int getNumberOfStates() const;
    void init(const SiteContainer & sites) throw (Exception);
    void reInit() throw (Exception);
};
