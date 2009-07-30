//
// File: TreeTemplateTools.h
// Created by:  Julien Dutheil
// Created on: Fri Oct  13 13:00 2006
// From file TreeTools.h
// Created on: Wed Aug  6 13:45:28 2003
//

/*
Copyright or © or Copr. CNRS, (November 16, 2004)

This software is a computer program whose purpose is to provide classes
for phylogenetic data analysis.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#ifndef _TREETEMPLATETOOLS_H_
#define _TREETEMPLATETOOLS_H_

#include "TreeTools.h"

//From the STL:
#include <vector>

using namespace std;

namespace bpp
{

template<class N> class TreeTemplate;

/**
 * @brief Utilitary methods working with TreeTemplate and Node objects.
 *
 * @see TreeTools for more generic methods.
 */
class TreeTemplateTools
{
  public:
    TreeTemplateTools() {}
    virtual ~TreeTemplateTools() {}

  public:
    
    /**
     * @name Retrieve topology information
     *
     * @{
     */

    /**
     * @brief Retrieve all leaves from a subtree.
     *
     * @param node The node that defines the subtree.
     * @return A vector of pointers toward each leaf in the subtree.
     */
    template<class N>
    static vector<N *> getLeaves(N & node)
    {
      vector<N *> leaves;
      getLeaves<N>(node, leaves);
      return leaves;
    }

    /**
     * @brief Retrieve all leaves from a subtree.
     *
     * @param node The node that defines the subtree.
     * @param leaves A vector of pointers toward each leaf in the subtree.
     */
    template<class N>
    static void getLeaves(N & node, vector<N *> & leaves)
    {
      if(node.isLeaf())
      {
        leaves.push_back(& node);
      }
      for(unsigned int i = 0; i < node.getNumberOfSons(); i++)
      {
        getLeaves<N>(* node.getSon(i), leaves);
      }
    }

    /**
     * @brief Retrieve all leaves ids from a subtree.
     *
     * @param node The node that defines the subtree.
     * @return A vector of ids.
     */
    static vector<int> getLeavesId(const Node & node)
    {
      vector<int> ids;
      getLeavesId(node, ids);
      return ids;
    }

    /**
     * @brief Retrieve all leaves ids from a subtree.
     *
     * @param node The node that defines the subtree.
     * @param ids A vector of ids.
     */
    static void getLeavesId(const Node & node, vector<int> & ids)
    {
      if(node.isLeaf()) {
        ids.push_back(node.getId());
      }
      for(unsigned int i = 0; i < node.getNumberOfSons(); i++) {
        getLeavesId(* node.getSon(i), ids);
      }
    }
    
    /**
     * @brief Get the id of a leaf given its name in a subtree.
     *
     * @param node The node defining the subtree to search.
     * @param name The name of the node.
     * @return The id of the node.
     * @throw NodeNotFoundException If the node is not found.
     */
    static int getLeafId(const Node & node, const string & name) throw (NodeNotFoundException)
    {
      int * id = NULL;
      searchLeaf(node, name, id);
      if(id == NULL) throw NodeNotFoundException("TreeTemplateTools::getLeafId().", name);
      else
      {
        int i = *id;
        delete id;
        return i;
      }
    }

    /**
     * @brief Get the id of a leaf given its name in a subtree.
     *
     * @param node The node defining the subtree to search.
     * @param name The name of the node.
     * @param id The id of the node.
     * @throw NodeNotFoundException If the node is not found.
     */
    static void searchLeaf(const Node & node, const string & name, int * & id) throw (NodeNotFoundException)
    {
      if(node.isLeaf())
      {
        if(node.getName() == name)
        {
          id = new int(node.getId());
          return;
        }
      }
      for(unsigned int i = 0; i < node.getNumberOfSons(); i++)
      {
        searchLeaf(* node.getSon(i), name, id);
      }
    }


    /**
     * @brief Retrieve all son nodes from a subtree.
     *
     * @param node The node that defines the subtree.
     * @return A vector of pointers toward each son node in the subtree.
     */
    template<class N>
    static vector<N *> getNodes(N & node)
    {
      vector<N *> nodes;
      getNodes<N>(node, nodes);
      return nodes;
    }

    /**
     * @brief Retrieve all son nodes from a subtree.
     *
     * @param node The node that defines the subtree.
     * @param nodes A vector of pointers toward each son node in the subtree.
     */
    template<class N>
    static void getNodes(N & node, vector<N *> & nodes)
    {
      for(unsigned int i = 0; i < node.getNumberOfSons(); i++)
      {
        getNodes<N>(* node.getSon(i), nodes);
      }
      nodes.push_back(& node);
    }

    /**
     * @brief Retrieve all nodes ids from a subtree.
     *
     * @param node The node that defines the subtree.
     * @return A vector of ids.
     */
    static vector<int> getNodesId(const Node & node)
    {
      vector<int> ids;
      getNodesId(node, ids);
      return ids;
    }

    /**
     * @brief Retrieve all nodes ids from a subtree.
     *
     * @param node The node that defines the subtree.
     * @param ids A vector of ids.
     */
    static void getNodesId(const Node & node, vector<int> & ids)
    {
      for(unsigned int i = 0; i < node.getNumberOfSons(); i++)
      {
        getNodesId(* node.getSon(i), ids);
      }
      ids.push_back(node.getId());
    }

    /**
     * @brief Retrieve all inner nodes from a subtree.
     *
     * @param node The node that defines the subtree.
     * @return A vector of pointers toward each inner node in the subtree.
     */
    template<class N>
    static vector<N *> getInnerNodes(N & node)
    {
      vector<N *> nodes;
      getInnerNodes<N>(node, nodes);
      return nodes;
    }

    /**
     * @brief Retrieve all inner nodes from a subtree.
     *
     * @param node The node that defines the subtree.
     * @param nodes A vector to be filled with pointers toward each inner node in the subtree.
     */
    template<class N>
    static void getInnerNodes(N & node, vector<N *> & nodes)
    {
      if(node.isLeaf()) return; //Do not add leaves!
      for(unsigned int i = 0; i < node.getNumberOfSons(); i++) {
        getInnerNodes<N>(* node.getSon(i), nodes);
      }
      nodes.push_back(& node);
    }

    /**
     * @brief Retrieve all inner nodes ids from a subtree.
     *
     * @param node The node that defines the subtree.
     * @return A vector of ids.
     */
    static vector<int> getInnerNodesId(const Node & node)
    {
      vector<int> ids;
      getInnerNodesId(node, ids);
      return ids;
    }

    /**
     * @brief Retrieve all inner nodes ids from a subtree.
     *
     * @param node The node that defines the subtree.
     * @param ids  A vector to be filled with the resulting ids.
     */
    static void getInnerNodesId(const Node & node, vector<int> & ids)
    {
      if(node.isLeaf()) return; //Do not add leaves!
      for(unsigned int i = 0; i < node.getNumberOfSons(); i++) {
        getInnerNodesId(* node.getSon(i), ids);
      }
      ids.push_back(node.getId());
    }

    /**
     * @param node The node defining the subtree to be searched.
     * @param id   The id to search for.
     * @return     Nodes with the specified id.
     */
    template<class N>
    static vector<N *> searchNodeWithId(N & node, int id)
    {
      vector<N *> nodes;
      searchNodeWithId<N>(node, id, nodes);
      return nodes;    
    }

    /**
     * @param node  The node defining the subtree to be searched.
     * @param id    The id to search for.
     * @param nodes A vector to be filled with the matching nodes.
     */
    template<class N>
    static void searchNodeWithId(N & node, int id, vector<N *> & nodes)
    {
      for(unsigned int i = 0; i < node.getNumberOfSons(); i++)
      {
        searchNodeWithId<N>(* node.getSon(i), id, nodes);
      }
      if(node.getId() == id) nodes.push_back(& node);
    }

    /**
     * @param node The node defining the subtree to be searched.
     * @param id   The id to search for.
     * @return     True if the subtree contains a node with the specified id.
     */
    template<class N>
    static bool hasNodeWithId(const N & node, int id)
    {
      if(node.getId() == id) return true;
      else
      {
        for(unsigned int i = 0; i < node.getNumberOfSons(); i++)
        {
          if(hasNodeWithId(*node.getSon(i), id)) return true;
        }
        return false;
      }
    }

    /**
     * @param node The node defining the subtree to be searched.
     * @param name The name to search for.
     * @return     Nodes with the specified name.
     */
    template<class N>
    static vector<N *> searchNodeWithName(N & node, const string & name)
    {
      vector<N *> nodes;
      //searchNodeWithId<N>(node, name, nodes);
      searchNodeWithName<N>(node, name, nodes);
      return nodes;    
    }

    /**
     * @param node  The node defining the subtree to be searched.
     * @param name  The name to search for.
     * @param nodes A vector to be filled with the matching nodes.
     */
    template<class N>
    static void searchNodeWithName(N & node, const string & name, vector<N *> & nodes)
    {
      for(unsigned int i = 0; i < node.getNumberOfSons(); i++)
      {
        searchNodeWithName<N>(* node.getSon(i), name, nodes);
      }
      if(node.hasName() && node.getName() == name) nodes.push_back(& node);
    }

    /**
     * @param node The node defining the subtree to be searched.
     * @param name The name to search for.
     * @return     True if the subtree contains a node with the specified name.
     */
    template<class N>
    static bool hasNodeWithName(const N & node, const string & name)
    {
      if(node.hasName() & node.getName() == name) return true;
      else
      {
        for(unsigned int i = 0; i < node.getNumberOfSons(); i++)
        {
          if(hasNodeWithName(*node.getSon(i), name)) return true;
        }
        return false;
      }
    }

    /**
     * @brief Tell if a particular node is the root of a tree
     * i.e. if it has a father node.
     *
     * @param node The node to check.
     * @return True if node has a father.
     */
    static bool isRoot(const Node & node) { return !node.hasFather(); }

    /**
     * @brief Get the number of leaves of a subtree defined by a particular node.
     *
     * @param node The node defining the subtree to check.
     * @return The number of leaves.
     */
    static unsigned int getNumberOfLeaves(const Node & node);

    /**
     * @brief Get the number of nodes of a subtree defined by a particular node.
     *
     * @param node The node defining the subtree to check.
     * @return The number of leaves.
     */
    static unsigned int getNumberOfNodes(const Node & node);

    /**
     * @brief Get the leaves names of a subtree defined by a particular node.
     *
     * @param node The node defining the subtree to check.
     * @return The list of all leaves names.
     */
    static vector<string> getLeavesNames(const Node & node);

    /**
     * @brief Get the depth of the subtree defined by node 'node', i.e. the maximum
     * number of sons 'generations'.
     *
     * ex:
     * <code>
     *    +----------A
     *    |
     * ---+ N1     +-------B
     *    |        |
     *    +--------+ N2
     *             |
     *             +------C
     * </code>
     * Depth of node 'N1' id 2, depth of node 'N2' is 1, depth of leaves is 0.
     *
     * @param node The node defining the subtree to check.
     * @return The depth of the subtree.
     */
    static unsigned int getDepth(const Node & node);

    /**
     * @brief Get the height of the subtree defined by node 'node', i.e. the maximum
     * distance between leaves and the root of the subtree.
     *
     * The distance do not include the branch length of the subtree root node.
     * The height of a leaf is hence 0.
     *
     * @param node The node defining the subtree to check.
     * @return The height of the subtree.
     * @throw NodeException If a branch length is lacking.
     */ 
    static double getHeight(const Node & node) throw (NodeException);

    /**
     * @brief Get the heights of all nodes within a subtree defined by node 'node', i.e. the maximum
     * distance between leaves and the root of the subtree.
     *
     * The height of a leaf is 0.
     *
     * @param node The node defining the subtree to check.
     * @param heights The map that will contain all the heights of the nodes, with node pointers as keys.
     * @return The height of the subtree.
     * @throw NodeException If a branch length is lacking.
     */ 
    static double getHeights(const Node & node, map<const Node *, double> & heights) throw (NodeException);

    /**
     * @brief Tell is a subtree is multifurcating.
     *
     * @param node The root node of the subtree.
     * @return True is the subtree contains at least one multifurcating
     * node (including the root node).
     */
    static bool isMultifurcating(const Node & node);

    static vector<Node *> getPathBetweenAnyTwoNodes(Node & node1, Node & node2, bool includeAncestor = true);
    
    static vector<const Node *> getPathBetweenAnyTwoNodes(const Node & node1, const Node & node2, bool includeAncestor = true);
     
    template<class N>
    static N * cloneSubtree(const Node & node) 
    {
      //First we copy this node using default copy constuctor:
      N * clone = new N(node);
      //Now we perform a hard copy:
      for(unsigned int i = 0; i < node.getNumberOfSons(); i++)
      {
        clone->setSon(i, * cloneSubtree<N>(* node[i]));
      }
      return clone;
    }
    
    template<class N>
    static N * cloneSubtree(const Tree & tree, int nodeId) 
    {
      //First we copy this node using default copy constuctor:
      N * clone = tree.hasNodeName(nodeId) ? new N(nodeId, tree.getNodeName(nodeId)) : new N(nodeId);
      if(tree.hasDistanceToFather(nodeId))
        clone->setDistanceToFather(tree.getDistanceToFather(nodeId));
      //Now we copy all sons:
      vector<int> sonsId = tree.getSonsId(nodeId);
      for(unsigned int i = 0; i < sonsId.size(); i++)
      {
        clone->addSon(* cloneSubtree<N>(tree, sonsId[i]));
      }
      //Must copy all properties too:
      vector<string> names;
      names = tree.getNodePropertyNames(nodeId);
      for(unsigned int i = 0; i < names.size(); i++)
      {
        clone->setNodeProperty(names[i], *tree.getNodeProperty(nodeId, names[i]));
      }
      names = tree.getBranchPropertyNames(nodeId);
      for(unsigned int i = 0; i < names.size(); i++)
      {
        clone->setBranchProperty(names[i], *tree.getBranchProperty(nodeId, names[i]));
      }
      
      return clone;
    }
    /** @} */
 
    /**
     * @name Act on branch lengths.
     *
     * @{
     */
    
    /**
     * @brief Get all the branch lengths of a subtree.
     *
     * @param node The root node of the subtree.
     * @return A vector with all branch lengths.
     * @throw NodeException If a branch length is lacking.
     */
    static Vdouble getBranchLengths(const Node & node) throw (NodeException);

    /**
     * @brief Get the total length (sum of all branch lengths) of a subtree.
     *
     * @param node The root node of the subtree.
     * @param includeAncestor Tell if the branch length of the most ancient node should be included in the counting.
     * (this should be set to false if this node is the root of the tree for instance).
      * @return The total length of the subtree.
     * @throw NodeException If a branch length is lacking.
     */
    static double getTotalLength(const Node & node, bool includeAncestor = true) throw (NodeException);
    
    /**
     * @brief Set all the branch lengths of a subtree.
     *
     * @param node  The root node of the subtree.
     * @param brLen The branch length to apply.
     */
    static void setBranchLengths(Node & node, double brLen);
     
    /**
     * @brief Remove all the branch lengths of a subtree.
     *
     * @param node  The root node of the subtree.
     */
    static void deleteBranchLengths(Node & node);

    /**
     * @brief Give a length to branches that don't have one in a subtree.
     *
     * @param node  The root node of the subtree.
     * @param brLen The branch length to apply.
     */
    static void setVoidBranchLengths(Node & node, double brLen);
        
    /**
     * @brief Scale a given tree.
     *
     * Multiply all branch lengths by a given factor.
     *
     * @param node   The root node of the subtree to scale.
     * @param factor The factor to multiply all branch lengths with.
     * @throw NodeException If a branch length is lacking.
     */
    static void scaleTree(Node & node, double factor) throw (NodeException);
   
    /**
     * @brief Get the total distance between to nodes.
     *
     * Sum all branch lengths between two nodes.
     *
     * @param node1 The first node.
     * @param node2 The second node.
     * @return The sum of all branch lengths between the two nodes.
     */
    static double getDistanceBetweenAnyTwoNodes(const Node & node1, const Node & node2);

    /**
     * @brief Compute a distance matrix from a tree.
     *
     * Compute all distances between each leaves and store them in a matrix.
     * A new DistanceMatrix object is created, and a pointer toward it is returned.
     * The destruction of this matrix is left up to the user.
     *
     * @see getDistanceBetweenAnyTwoNodes
     *
     * @param tree The tree to use.
     * @return The distance matrix computed from tree.
     */
    static DistanceMatrix * getDistanceMatrix(const TreeTemplate<Node> & tree);

    /** @} */

    /**
     * @name Conversion tools.
     *
     * Convert from Newick standard tree description.
     * The description is for a node, and hence is to be surrounded with
     * parenthesis. ex: (A:0.001, (B:0.001, C:0.02)90:0.005)50:0.0005
     *
     * @{
     */

    /**
     * @brief Parse a string in the parenthesis format and convert it to
     * a subtree.
     *
     * @param description the string to parse;
     * @param bootstrap Tell is real bootstrap values are expected. If so, a property with name TreeTools::BOOTSTRAP will be created and stored at the corresponding node.
     * The property value will be of type Number<double>. Otherwise, an object of type String will be created and stored with the property name propertyName.
     * @param propertyName The name of the property to store. Only used if bootstrap = false.
     * @return A pointer toward a dynamically created subtree.
     */
    static Node * parenthesisToNode(const string & description, bool bootstrap=true, const string & propertyName=TreeTools::BOOTSTRAP);
  
    /**
     * @brief Parse a string in the parenthesis format and convert it to
     * a tree.
     *
     * @param description the string to parse;
     * @param bootstrap Tell is real bootstrap values are expected. If so, a property with name TreeTools::BOOTSTRAP will be created and stored at the corresponding node.
     * The property value will be of type Number<double>. Otherwise, an object of type String will be created and stored with the property name propertyName.
     * @param propertyName The name of the property to store. Only used if bootstrap = false.
     * @return A pointer toward a dynamically created tree.
     * @throw Exception in case of bad format.
     */
    static TreeTemplate<Node> * parenthesisToTree(const string & description, bool bootstrap=true, const string & propertyName=TreeTools::BOOTSTRAP) throw (Exception);
    
    /**
     * @brief Get the parenthesis description of a subtree.
     *
     * @param node The node defining the subtree.
     * @param writeId Tells if node ids must be printed.
     *                This will overwrite bootstrap values if there are ones.
     *                Leaves id will be added to the leave names, separated by a '_' character.
     * @return A string in the parenthesis format.
     */
    static string nodeToParenthesis(const Node & node, bool writeId = false);

    /**
     * @brief Get the parenthesis description of a subtree.
     *
     * @param node The node defining the subtree.
     * @param bootstrap Tell is bootstrap values must be writen.
     * If so, the content of the property with name TreeTools::BOOTSTRAP will be written as bootstrap value.
     * The property should be a Number<double> object.
     * Otherwise, the content of the property with name 'propertyName' will be written.
     * In this later case, the property should be a String object.
     * @param propertyName The name of the property to use. Only used if bootstrap = false.
     * @return A string in the parenthesis format.
     */
    static string nodeToParenthesis(const Node & node, bool bootstrap, const string & propertyName);

    /**
     * @brief Get the parenthesis description of a tree.
     *
     * @param tree The tree to convert.
     * @param writeId Tells if node ids must be printed.
     *                This will overwrite bootstrap values if there are ones.
     *                Leaves id will be added to the leave names, separated by a '_' character.
     * @return A string in the parenthesis format.
     */
    static string treeToParenthesis(const TreeTemplate<Node> & tree, bool writeId = false);
    
    /**
     * @brief Get the parenthesis description of a tree.
     *
     * @param tree The tree to convert.
     * @param bootstrap Tell is bootstrap values must be writen.
     * If so, the content of the property with name TreeTools::BOOTSTRAP will be written as bootstrap value.
     * The property should be a Number<double> object.
     * Otherwise, the content of the property with name 'propertyName' will be written.
     * In this later case, the property should be a String object.
     * @param propertyName The name of the property to use. Only used if bootstrap = false.
     * @return A string in the parenthesis format.
     */
    static string treeToParenthesis(const TreeTemplate<Node> & tree, bool bootstrap, const string & propertyName);
  
    /** @} */

    /**
     * @name Random trees
     *
     * @{
     */

    /**
     * @brief Draw a random tree from a list of taxa.
     *
     * @param leavesNames A list of taxa.
     * @return A random tree with all corresponding taxa.
     */
    static TreeTemplate<Node> * getRandomTree(vector<string> & leavesNames);

    /** @} */
    
    /**
     * @brief Get a subset of node neighbors.
     *
     * Get all neighbors of node node1 that are neither node1 nor node2.
     * This method is useful for topology manipulations, like NNI.
     *
     * @param node1 The node whose neighbors must be retrieved.
     * @param node2 One neighbor to exclude.
     * @param node3 Another neighbor to exclude.
     * @return A vector of neighbors.
     */
    static vector<const Node *> getRemainingNeighbors(const Node * node1, const Node * node2, const Node * node3);
 
    /**
     * @brief This method will add a given value (possibly negative) to all identifiers in a (sub)tree.
     *
     * @param node The root node of the (sub)tree to use.
     * @param increment The value to add.
     */
    static void incrementAllIds(Node * node, int increment);
    
};

} //end of namespace bpp.

#endif //_TREETEMPLATETOOLS_H_

