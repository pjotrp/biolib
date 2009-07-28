%module bpptest
%{
#include "NNITopologySearch.h"
using namespace bpp;
%}
%include "TopologySearch.i"
%include "NNISearchable.i"

class NNITopologySearch:public virtual TopologySearch
{
  public:
    static const string FAST;
    static const string BETTER;
    static const string PHYML;

    NNITopologySearch(NNISearchable & tree, const string & algorithm = FAST, unsigned int verbose = 2);
    virtual ~NNITopologySearch();

    void search() throw (Exception);
    void addTopologyListener(TopologyListener & listener);

    const Tree * getTopology() const;
    NNISearchable * getSearchableObject();
    const NNISearchable * getSearchableObject() const;
};
