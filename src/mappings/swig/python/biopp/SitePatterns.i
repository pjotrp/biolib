%module bpptest
%{
#include "SitePatterns.h"
using namespace bpp;
%}
%include "Tree.i"
%include "Clonable.i"
%include "VectorTools.i"
%include "SiteContainer.i"
%include "Site.i"
%include "std_map.i"
using namespace std;

%rename(__assign__) SitePatterns::operator=;

class SitePatterns:public virtual Clonable
{
  public:
    SitePatterns(const SiteContainer * sequences, bool own = false);
    virtual ~SitePatterns();
    SitePatterns(const SitePatterns & patterns);
    SitePatterns& operator=(const SitePatterns & patterns);
    SitePatterns *clone() const;

    const vector<unsigned int> getWeights() const;
    const vector<unsigned int> getIndices() const;
    SiteContainer * getSites() const;
};
