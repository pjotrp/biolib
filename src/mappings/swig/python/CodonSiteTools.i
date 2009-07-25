%module bpptest
%{
#include "CodonSiteTools.h"
using namespace bpp;
%}
%include "SymbolListTools.i"
%include "Site.i"
%include "CodonAlphabet.i"
%include "GeneticCode.i"
%include "Exceptions.i"
%include "std_map.i"
using namespace std;

class CodonSiteTools:public SymbolListTools
{
  public:
    CodonSiteTools();
    virtual ~CodonSiteTools();

    static bool hasGapOrStop(const Site & site) throw (AlphabetException);
    static bool hasStop(const Site & site) throw (AlphabetException);
    static bool isMonoSitePolymorphic(const Site & site) throw (AlphabetException, EmptySiteException);
    static bool isSynonymousPolymorphic(const Site & site, const GeneticCode & gc) throw (AlphabetException, AlphabetMismatchException, EmptySiteException);
    static Site * generateCodonSiteWithoutRareVariant(const Site & site, double freqmin) throw(AlphabetException, EmptySiteException);
    static unsigned int numberOfDifferences(int i, int j, const CodonAlphabet & ca);
    static double numberOfSynonymousDifferences(int i, int j, const GeneticCode & gc, bool minchange=false);
    static double piSynonymous(const Site & site, const GeneticCode & gc, bool minchange=false) throw (AlphabetException, AlphabetMismatchException, EmptySiteException);
    static double piNonSynonymous(const Site & site, const GeneticCode & gc, bool minchange = false) throw (AlphabetException, AlphabetMismatchException, EmptySiteException);
    static double numberOfSynonymousPositions(int i, const GeneticCode & gc,  double ratio=1.0) throw (Exception);
    static double meanNumberOfSynonymousPositions(const Site & site, const GeneticCode & gc, double ratio=1) throw (AlphabetException, AlphabetMismatchException, EmptySiteException);
    static unsigned int numberOfSubsitutions(const Site & site, double freqmin = 0.) throw(AlphabetException, EmptySiteException);
    static unsigned int numberOfNonSynonymousSubstitutions(const Site & site, const GeneticCode & gc, double freqmin = 0.) throw (AlphabetException, AlphabetMismatchException, EmptySiteException);
    static vector<unsigned int> fixedDifferences(const Site & siteIn, const Site & siteOut, int i, int j, const GeneticCode & gc) throw (AlphabetException, AlphabetMismatchException, EmptySiteException);
};
