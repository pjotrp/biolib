%module bpptest
%{
#include "PGMA.h"
using namespace bpp;
%}
%include "AbstractAgglomerativeDistanceMethod.i"
%include "Tree.i"
%include "TreeTemplate.i"

struct PGMAInfos
{
  unsigned int numberOfLeaves;
  double time;
};

class PGMA:public AbstractAgglomerativeDistanceMethod
{
  public:
    PGMA(bool weighted = true): _weighted(weighted);
    PGMA(const DistanceMatrix & matrix, bool weighted = true, bool verbose = true) throw (Exception);
    virtual ~PGMA();

    void setDistanceMatrix(const DistanceMatrix & matrix);
    TreeTemplate<Node> * getTree() const;
    void setWeighted(bool weighted);
    bool isWeighted() const;
};
