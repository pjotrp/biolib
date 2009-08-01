%module bpptest
%{
#include "SiteTools.h"
using namespace bpp;
%}

%include "SymbolListTools.i"
%include "Site.i"
%include "Exceptions.i"
%include "std_map.i"

using namespace std;

%ignore SiteTools::SiteTools;
%ignore SiteTools::~SiteTools;

class SiteTools:public SymbolListTools
{
  public:
    SiteTools();
    virtual ~SiteTools();

    static bool hasGap(const Site & site);
    static bool isGapOnly(const Site & site);
    static bool isGapOrUnresolvedOnly(const Site & site);
    static bool hasUnknown(const Site & site);
    static bool isComplete(const Site & site);
    static bool isConstant(const Site & site, bool ignoreUnknown = false) throw (EmptySiteException);
    static bool areSitesIdentical(const Site & site1, const Site & site2);
    static double variabilityShannon(const Site & site, bool resolveUnknowns) throw (EmptySiteException);
    static double variabilityFactorial(const Site & site) throw (EmptySiteException);
    static double mutualInformation(const Site & site1, const Site & site2, bool resolveUnknowns) throw (DimensionException,EmptySiteException);
    static double heterozygosity(const Site & site) throw (EmptySiteException);
    static unsigned int getNumberOfDistinctCharacters(const Site & site) throw (EmptySiteException);
    static bool hasSingleton(const Site & site) throw (EmptySiteException);
    static bool isParsimonyInformativeSite(const Site & site) throw (EmptySiteException);
    static bool isTriplet(const Site & site) throw (EmptySiteException);
};
