%module bpptest
%{
#include "TreeTemplateTools.h"
using namespace bpp;
%}
%include "TreeTools.i"
%include "std_vector.i"
using namespace std;

%ignore TreeTemplateTools::TreeTemplateTools;
%ignore TreeTemplateTools::~TreeTemplateTools;

template<class N> class TreeTemplate;
class TreeTemplateTools
{
  public:
    TreeTemplateTools();
    virtual ~TreeTemplateTools();

    template<class N> static vector<N *> getLeaves(N & node);
    template<class N> static void getLeaves(N & node, vector<N *> & leaves);
    static vector<int> getLeavesId(const Node & node);
    static void getLeavesId(const Node & node, vector<int> & ids);
    static int getLeafId(const Node & node, const string & name) throw (NodeNotFoundException);
    static void searchLeaf(const Node & node, const string & name, int * & id) throw (NodeNotFoundException);
    template<class N> static vector<N *> getNodes(N & node);
    template<class N> static void getNodes(N & node, vector<N *> & nodes);
    static vector<int> getNodesId(const Node & node);
    static void getNodesId(const Node & node, vector<int> & ids);
    template<class N> static vector<N *> getInnerNodes(N & node);
    template<class N> static void getInnerNodes(N & node, vector<N *> & nodes);
    static vector<int> getInnerNodesId(const Node & node);
    static void getInnerNodesId(const Node & node, vector<int> & ids);
    template<class N> static vector<N *> searchNodeWithId(N & node, int id);
    template<class N> static void searchNodeWithId(N & node, int id, vector<N *> & nodes);
    template<class N> static bool hasNodeWithId(const N & node, int id);
    template<class N> static vector<N *> searchNodeWithName(N & node, const string & name);
    template<class N> static void searchNodeWithName(N & node, const string & name, vector<N *> & nodes);
    template<class N> static bool hasNodeWithName(const N & node, const string & name);
    static bool isRoot(const Node & node);
    static unsigned int getNumberOfLeaves(const Node & node);
    static unsigned int getNumberOfNodes(const Node & node);
    static vector<string> getLeavesNames(const Node & node);
    static unsigned int getDepth(const Node & node);
    static double getHeight(const Node & node) throw (NodeException);
    static double getHeights(const Node & node, map<const Node *, double> & heights) throw (NodeException);
    static bool isMultifurcating(const Node & node);

    %ignore getPathBetweenAnyTwoNodes(const Node & node1, const Node & node2, bool includeAncestor = true);
    static vector<Node *> getPathBetweenAnyTwoNodes(Node & node1, Node & node2, bool includeAncestor = true);
    static vector<const Node *> getPathBetweenAnyTwoNodes(const Node & node1, const Node & node2, bool includeAncestor = true);

    template<class N> static N * cloneSubtree(const Node & node);
    template<class N> static N * cloneSubtree(const Tree & tree, int nodeId);
    static Vdouble getBranchLengths(const Node & node) throw (NodeException);
    static double getTotalLength(const Node & node, bool includeAncestor = true) throw (NodeException);
    static void setBranchLengths(Node & node, double brLen);
    static void deleteBranchLengths(Node & node);
    static void setVoidBranchLengths(Node & node, double brLen);
    static void scaleTree(Node & node, double factor) throw (NodeException);
    static double getDistanceBetweenAnyTwoNodes(const Node & node1, const Node & node2);
    static DistanceMatrix * getDistanceMatrix(const TreeTemplate<Node> & tree);
    static Node * parenthesisToNode(const string & description, bool bootstrap=true, const string & propertyName=TreeTools::BOOTSTRAP);
    static TreeTemplate<Node> * parenthesisToTree(const string & description, bool bootstrap=true, const string & propertyName=TreeTools::BOOTSTRAP) throw (Exception);
    static string nodeToParenthesis(const Node & node, bool writeId = false);
    static string nodeToParenthesis(const Node & node, bool bootstrap, const string & propertyName);
    static string treeToParenthesis(const TreeTemplate<Node> & tree, bool writeId = false);
    static string treeToParenthesis(const TreeTemplate<Node> & tree, bool bootstrap, const string & propertyName);
    static TreeTemplate<Node> * getRandomTree(vector<string> & leavesNames);
    static vector<const Node *> getRemainingNeighbors(const Node * node1, const Node * node2, const Node * node3);
    static void incrementAllIds(Node * node, int increment);
};

%template(intGetLeaves) TreeTemplateTools::getLeaves<int>;
%template(doubleGetLeaves) TreeTemplateTools::getLeaves<double>;
%template(intGetNodes) TreeTemplateTools::getNodes<int>;
%template(doubleGetNodes) TreeTemplateTools::getNodes<double>;
%template(intGetInnerNodes) TreeTemplateTools::getInnerNodes<int>;
%template(doubleGetInnerNodes) TreeTemplateTools::getInnerNodes<double>;

%template(intSearchNodeWithId) TreeTemplateTools::searchNodeWithId<int>;
%template(doubleSearchNodeWithId) TreeTemplateTools::searchNodeWithId<double>;
%template(intHasNodeWithId) TreeTemplateTools::hasNodeWithId<int>;
%template(doubleHasNodeWithId) TreeTemplateTools::hasNodeWithId<double>;
%template(intSearchNodeWithName) TreeTemplateTools::searchNodeWithName<int>;
%template(doubleSearchNodeWithName) TreeTemplateTools::searchNodeWithName<double>;
%template(intHasNodeWithName) TreeTemplateTools::hasNodeWithName<int>;
%template(doubleHasNodeWithName) TreeTemplateTools::hasNodeWithName<double>;

%template(intCloneSubtree) TreeTemplateTools::cloneSubtree<int>;
%template(doubleCloneSubtree) TreeTemplateTools::cloneSubtree<double>;
