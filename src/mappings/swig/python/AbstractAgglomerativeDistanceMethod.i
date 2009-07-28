%module bpptest
%{
#include "AbstractAgglomerativeDistanceMethod.h"
using namespace bpp;
%}
%include "AgglomerativeDistanceMethod.i"
%include "Node.i"
%include "TreeTemplate.i"
%include "std_map.i"
using namespace std;

%rename(__assign__) AbstractAgglomerativeDistanceMethod::operator=;

class AbstractAgglomerativeDistanceMethod:public virtual AgglomerativeDistanceMethod
{
  public:
    AbstractAgglomerativeDistanceMethod();
    AbstractAgglomerativeDistanceMethod(bool verbose);
    AbstractAgglomerativeDistanceMethod(const DistanceMatrix & matrix, bool verbose = true);
    virtual ~AbstractAgglomerativeDistanceMethod();
    AbstractAgglomerativeDistanceMethod(const AbstractAgglomerativeDistanceMethod & a);
    AbstractAgglomerativeDistanceMethod & operator=(const AbstractAgglomerativeDistanceMethod & a);

    virtual void setDistanceMatrix(const DistanceMatrix & matrix);
    virtual
    TreeTemplate<Node> * getTree() const;
    virtual void computeTree(bool rooted) throw (Exception);
    void setVerbose(bool yn);
    bool isVerbose() const;
};
