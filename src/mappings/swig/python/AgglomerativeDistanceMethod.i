%module bpptest
%{
#include "AgglomerativeDistanceMethod.h"
using namespace bpp;
%}

class DistanceMatrix;
class Node;
class Tree;
class AgglomerativeDistanceMethod
{
  public:
    AgglomerativeDistanceMethod();
    virtual ~AgglomerativeDistanceMethod();

    virtual void setDistanceMatrix(const DistanceMatrix & matrix) = 0;
    virtual void computeTree(bool rooted) = 0;
    virtual Tree * getTree() const = 0;
};
