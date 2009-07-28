%module bpptest
%{
#include "BipartitionList.h"
using namespace bpp;
%}
%include "Tree.i"
%include "std_map.i"
//#include <algorithm>
using namespace std;
%include "MapTools.i"
%include "Matrix.i"

class Node;
template<class N> class TreeTemplate;

%rename(__assign__) BipartitionList::operator=;

class BipartitionList:public virtual Clonable
{
  public:
    BipartitionList();
    BipartitionList(const Tree & tr, bool sorted = true, vector<int> * index = NULL);
    BipartitionList(const vector<string> & elements, const vector<int*> & bipl);
    BipartitionList(const BipartitionList & bipl);
    BipartitionList& operator=(const BipartitionList & bipl);
    virtual ~BipartitionList();
    BipartitionList* clone() const;

    unsigned int getNumberOfElements() const;
    const vector<string> & getElementNames() const;
    unsigned int getNumberOfBipartitions() const;
    const vector<int*> & getBitBipartitionList() const;
    map<string, bool> getBipartition(unsigned int i) const throw (Exception);
    int* getBitBipartition(unsigned int i) throw (Exception);
    bool haveSameElementsThan(map <string, bool> bipart) const;
    void addBipartition(map<string, bool> & bipart, bool checkElements = 1) throw(Exception);
    void deleteBipartition(unsigned int i) throw(Exception);
    bool isSorted() const;
    void sortElements();
    bool containsBipartition(map<string, bool> & bipart, bool checkElements = 1) const throw(Exception);
    bool areIdentical(unsigned int k1, unsigned int k2) const throw(Exception);
    void removeRedundantBipartitions();
    bool areCompatible(unsigned int k1, unsigned int k2) const throw(Exception);
    bool areAllCompatible() const;
    bool areAllCompatibleWith(map<string, bool> & bipart, bool checkElements = true) const throw (Exception);
    void removeTrivialBipartitions();
    void addTrivialBipartitions(bool checkExisting);
    void flip(unsigned int i) throw(Exception);
    unsigned int getPartitionSize(unsigned int i) const throw(Exception);
    void sortByPartitionSize();
    TreeTemplate<Node>* toTree() const throw(Exception);
    RowMatrix<int> toMatrix() const;
};
