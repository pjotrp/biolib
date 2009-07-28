%module bpptest
%{
#include "TreeTools.h"
using namespace bpp;
%}
%include "TreeExceptions.i"
%include "Node.i"
%include "Tree.i"
%include "BipartitionList.i"
%include "Exceptions.i"
%include "VectorTools.i"
%include "VectorSiteContainer.i"
%include "DistanceMatrix.i"

class NodeTokenizer
{
  public:
    NodeTokenizer(const string & description) throw (IOException): tokens(), currentPosition(0);
    string next() const;
    bool hasNext() const;
};

class TreeTools
{
  public:
    TreeTools();
    virtual ~TreeTools();

    static vector<int> getLeavesId(const Tree & tree, int nodeId) throw (NodeNotFoundException);
    static void getLeavesId(const Tree & tree, int nodeId, vector<int> & leaves) throw (NodeNotFoundException);
    static int getLeafId(const Tree & tree, int nodeId, const string & name) throw (NodeNotFoundException);
    static void searchLeaf(const Tree & tree, int nodeId, const string & name, int * & id) throw (NodeNotFoundException);
    static vector<int> getPathBetweenAnyTwoNodes(const Tree & tree, int nodeId1, int nodeId2, bool includeAncestor = true) throw (NodeNotFoundException);
    static vector<int> getAncestors(const Tree & tree, int nodeId) throw (NodeNotFoundException);
    static int getLastCommonAncestor(const Tree & tree, const vector<int>& nodeIds) throw (NodeNotFoundException, Exception);
    static unsigned int getDepth(const Tree & tree, int nodeId) throw (NodeNotFoundException);
    static double getHeight(const Tree & tree, int nodeId) throw (NodeNotFoundException,NodeException);
    static Vdouble getBranchLengths(const Tree & tree, int nodeId) throw (NodeNotFoundException,NodeException);
    static double getTotalLength(const Tree & tree, int nodeId, bool includeAncestor = true) throw (NodeNotFoundException,NodeException);
    static void setBranchLengths(Tree & tree, int nodeId, double brLen) throw (NodeNotFoundException);
    static void setVoidBranchLengths(Tree & tree, int nodeId, double brLen) throw (NodeNotFoundException);
    static void scaleTree(Tree & tree, int nodeId, double factor) throw (NodeNotFoundException,NodeException);
    static void initBranchLengthsGrafen(Tree & tree);
    static void computeBranchLengthsGrafen(Tree & tree, double power=1, bool init=true) throw (NodeException);

    static double convertToClockTree(Tree & tree, int nodeId, bool noneg=false) throw (NodeNotFoundException,NodeException);
    static double convertToClockTree2(Tree & tree, int nodeId) throw (NodeNotFoundException,NodeException);
    static double getDistanceBetweenAnyTwoNodes(const Tree & tree, int nodeId1, int nodeId2) throw (NodeNotFoundException);
    static DistanceMatrix * getDistanceMatrix(const Tree & tree);
    static void midpointRooting(Tree & tree);
    static Element getElement(const string & elt) throw (IOException);
    static string nodeToParenthesis(const Tree & tree, int nodeId, bool writeId = false) throw (NodeNotFoundException);
    static string nodeToParenthesis(const Tree & tree, int nodeId, bool bootstrap, const string & propertyName) throw (NodeNotFoundException);
    static string treeToParenthesis(const Tree & tree, bool writeId = false);
    static string treeToParenthesis(const Tree & tree, bool bootstrap, const string & propertyName);
    static vector<int> getNodesId(const Tree & tree, int nodeId) throw (NodeNotFoundException);
    static void getNodesId(const Tree & tree, int nodeId, vector<int> & nodes) throw (NodeNotFoundException);
    static int getMaxId(const Tree & tree, int id);
    static int getMPNUId(const Tree & tree, int id);
    static bool checkIds(const Tree & tree, bool throwException) throw (Exception);
    static VectorSiteContainer* MRPEncode(const vector<Tree *> & vecTr);
    static bool haveSameTopology(const Tree & tr1, const Tree & tr2);
    static int robinsonFouldsDistance(const Tree & tr1, const Tree & tr2, bool checkNames = true, int* missing_in_tr2 = NULL, int* missing_in_tr1 = NULL) throw (Exception);
    static BipartitionList * bipartitionOccurrences(const vector<Tree *> & vecTr, vector<unsigned int> & bipScore);
    static TreeTemplate<Node>* thresholdConsensus(const vector<Tree *> & vecTr, double threshold, bool checkNames = true) throw (Exception);
    static TreeTemplate<Node>* fullyResolvedConsensus(const vector<Tree *> & vecTr, bool checkNames = true);
    static TreeTemplate<Node>* majorityConsensus(const vector<Tree *> & vecTr, bool checkNames = true);
    static TreeTemplate<Node>* strictConsensus(const vector<Tree *> & vecTr, bool checkNames = true);
    static Tree* MRP(const vector<Tree*> & vecTr);
    static void computeBootstrapValues(Tree & tree, const vector<Tree *> & vecTr, bool verbose = true);
    static const string BOOTSTRAP;   
};
