%module bpptest
%{
#include "TopologySearch.h"
using namespace bpp;
%}
%include "Exceptions.i"
%include "std_string.i"
%include "std_vector.i"
using namespace std;

class TopologyChangeEvent
{
  public:
    TopologyChangeEvent(): _message("");
    TopologyChangeEvent(const string & message): _message(message);
    virtual ~TopologyChangeEvent();

    virtual string getMessage() const;
};

class TopologyListener
{
  public:
    TopologyListener();
    virtual ~TopologyListener();

    virtual void topologyChangePerformed(const TopologyChangeEvent & event);
    virtual void topologyChangeTested(const TopologyChangeEvent & event) = 0;
    virtual void topologyChangeSuccessful(const TopologyChangeEvent & event) = 0;
};

%ignore TopologySearch::TopologySearch;
%ignore TopologySearch::~TopologySearch;

class TopologySearch
{
  public:
    TopologySearch();
    virtual ~TopologySearch();

    virtual void search() throw (Exception) = 0;
    virtual void addTopologyListener(TopologyListener & listener) = 0;
};
