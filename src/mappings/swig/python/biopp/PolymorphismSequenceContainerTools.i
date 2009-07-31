%module bpptest
%{
#include "PolymorphismSequenceContainerTools.h"
using namespace bpp;
%}
%include "CodonAlphabet.i"
%include "Mase.i"
%include "MaseTools.i"
%include "SequenceContainerTools.i"
%include "SiteIterator.i"
%include "SiteTools.i"
%include "VectorSiteContainer.i"
%include "RandomTools.i"
%include "StringTokenizer.i"
%include "std_map.i"
%include "PolymorphismSequenceContainer.i"
%include "GeneralExceptions.i"
using namespace std;

%ignore PolymorphismSequenceContainerTools::PolymorphismSequenceContainerTools;
%ignore PolymorphismSequenceContainerTools::~PolymorphismSequenceContainerTools;

class PolymorphismSequenceContainerTools
{
  public:
    ~PolymorphismSequenceContainerTools();

    static PolymorphismSequenceContainer * read(const string & path, const Alphabet * alpha) throw (Exception);
    static PolymorphismSequenceContainer * extractIngroup (const PolymorphismSequenceContainer & psc) throw (Exception);
    static PolymorphismSequenceContainer * extractOutgroup (const PolymorphismSequenceContainer & psc) throw (Exception);
    static PolymorphismSequenceContainer * extractGroup(const PolymorphismSequenceContainer & psc, unsigned int group_id) throw (Exception);
    static PolymorphismSequenceContainer * getSelectedSequences(const PolymorphismSequenceContainer & psc, SequenceSelection & ss);
    static PolymorphismSequenceContainer * sample(const PolymorphismSequenceContainer & psc, unsigned int n, bool replace = true);
    static PolymorphismSequenceContainer * getSitesWithoutGaps (const PolymorphismSequenceContainer & psc);
    static unsigned int getNumberOfNonGapSites(const PolymorphismSequenceContainer & psc, bool ingroup) throw (Exception);
    static unsigned int getNumberOfCompleteSites(const PolymorphismSequenceContainer & psc, bool ingroup) throw (Exception);
    static PolymorphismSequenceContainer * getCompleteSites(const PolymorphismSequenceContainer & psc);
    static PolymorphismSequenceContainer * excludeFlankingGap(const PolymorphismSequenceContainer & psc);
    static PolymorphismSequenceContainer * getSelectedSites(const PolymorphismSequenceContainer & psc, const string & setName, bool phase);
    static PolymorphismSequenceContainer * getNonCodingSites(const PolymorphismSequenceContainer & psc, const string & setName);
    static PolymorphismSequenceContainer * getOnePosition(const PolymorphismSequenceContainer & psc, const string & setName, unsigned int pos);
    static PolymorphismSequenceContainer * getIntrons(const PolymorphismSequenceContainer & psc, const string &setName, const CodonAlphabet *ca );
    static PolymorphismSequenceContainer * get5Prime(const PolymorphismSequenceContainer & psc, const string &setName);
    static PolymorphismSequenceContainer * get3Prime(const PolymorphismSequenceContainer & psc, const string &setName, const CodonAlphabet *ca );
    static string getIngroupSpeciesName(const PolymorphismSequenceContainer & psc);
};
