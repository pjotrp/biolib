%module bpptest
%{
#include "NNISearchable.h"
using namespace bpp;
%}
%include "Node.i"
%include "TreeTemplate.i"
%include "TopologySearch.i"

class NNISearchable:public TopologyListener,public virtual Clonable
{
  public:
    NNISearchable();
    virtual ~NNISearchable();
    virtual NNISearchable * clone() const = 0;

    virtual double testNNI(int nodeId) const throw (NodeException) = 0;
    virtual void doNNI(int nodeId) throw (NodeException) = 0;
    virtual const Tree * getTopology() const = 0;
    virtual double getTopologyValue() const throw (Exception) = 0;
};
