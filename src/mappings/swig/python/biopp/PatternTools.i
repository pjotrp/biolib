%module bpptest
%{
#include "PatternTools.h"
using namespace bpp;
%}
%include "Tree.i"
%include "VectorTools.i"
%include "SiteContainer.i"
%include "Site.i"
%include "std_map.i"
using namespace std;

class PatternTools
{
  public:
    static SiteContainer * getSequenceSubset(const SiteContainer & sequenceSet, const Node & node) throw (Exception);
    static SiteContainer * getSequenceSubset(const SiteContainer & sequenceSet, const vector<string> & names) throw (Exception);
    static SiteContainer * shrinkSiteSet(const SiteContainer & sequenceSet) throw (Exception);
    static Vint getIndexes(const SiteContainer & sequences1, const SiteContainer & sequences2);
};
