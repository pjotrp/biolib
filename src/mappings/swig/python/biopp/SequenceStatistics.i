%module bpptest
%{
#include "SequenceStatistics.h"
using namespace bpp;
%}
%include "SiteIterator.i"
%include "SiteContainer.i"
%include "SymbolListTools.i"
%include "CodonAlphabet.i"
%include "GeneticCode.i"
%include "SiteContainerTools.i"
%include "PolymorphismSequenceContainer.i"
using namespace std;

%ignore SequenceStatistics::SequenceStatistics;
%ignore SequenceStatistics::~SequenceStatistics;

class SequenceStatistics
{
  public:
    ~SequenceStatistics();

    static unsigned int polymorphicSiteNumber(const PolymorphismSequenceContainer & psc, bool gapflag = true);
    static unsigned int parsimonyInformativeSiteNumber(const PolymorphismSequenceContainer & psc, bool gapflag = true);
    static unsigned int countSingleton(const PolymorphismSequenceContainer & psc, bool gapflag = true);
    static unsigned int totNumberMutations(const PolymorphismSequenceContainer & psc, bool gapflag = true);
    static unsigned int totMutationsExternalBranchs(const PolymorphismSequenceContainer & ing, const PolymorphismSequenceContainer outg);
    static unsigned int tripletNumber(const PolymorphismSequenceContainer & psc, bool gapflag = true);
    static double heterozygosity(const PolymorphismSequenceContainer & psc, bool gapflag=true);
    static double squaredHeterozygosity(const PolymorphismSequenceContainer & psc, bool gapflag=true);
    static double gcContent(const PolymorphismSequenceContainer & psc);
    static vector<unsigned int> gcPolymorphism(const PolymorphismSequenceContainer & psc, bool stopflag = true);
    static double watterson75( const PolymorphismSequenceContainer & psc, bool gapflag = true );
    static double tajima83( const PolymorphismSequenceContainer & psc, bool gapflag = true );
    static unsigned int DVK ( const PolymorphismSequenceContainer & psc, bool gapflag = true );
    static double DVH ( const PolymorphismSequenceContainer & psc, bool gapflag = true );
    static unsigned int getNumberOfTransitions( const PolymorphismSequenceContainer & psc );
    static unsigned int getNumberOfTransversions( const PolymorphismSequenceContainer & psc );
    static double getTransitionsTransversionsRatio( const PolymorphismSequenceContainer & psc ) throw(Exception);
    static unsigned int stopCodonSiteNumber(const PolymorphismSequenceContainer & psc, bool gapflag = true);
    static unsigned int monoSitePolymorphicCodonNumber(const PolymorphismSequenceContainer & psc, bool stopflag = true, bool gapflag = true);
    static unsigned int synonymousPolymorphicCodonNumber(const PolymorphismSequenceContainer & psc, const GeneticCode & gc);
    static double watterson75Synonymous(const PolymorphismSequenceContainer & psc, const GeneticCode & gc);
    static double watterson75NonSynonymous(const PolymorphismSequenceContainer & psc, const GeneticCode & gc);
    static double piSynonymous(const PolymorphismSequenceContainer & psc, const GeneticCode & gc, bool minchange=false);
    static double piNonSynonymous(const PolymorphismSequenceContainer & psc, const GeneticCode & gc, bool minchange=false);
    static double meanSynonymousSitesNumber(const PolymorphismSequenceContainer & psc, const GeneticCode & gc, double ratio=1.0);
    static double meanNonSynonymousSitesNumber(const PolymorphismSequenceContainer & psc, const GeneticCode & gc, double ratio=1.0);
    static unsigned int synonymousSubstitutionsNumber(const PolymorphismSequenceContainer & psc, const GeneticCode & gc, double freqmin = 0);
    static unsigned int nonSynonymousSubstitutionsNumber(const PolymorphismSequenceContainer & psc, const GeneticCode & gc, double freqmin = 0);
    static vector<unsigned int> fixedDifferences(const PolymorphismSequenceContainer & pscin, const PolymorphismSequenceContainer & pscout, PolymorphismSequenceContainer & psccons, const GeneticCode & gc);
    static vector<unsigned int> MKtable(const PolymorphismSequenceContainer & ingroup, const PolymorphismSequenceContainer & outgroup , const GeneticCode & gc, double freqmin = 0);
    static double neutralityIndex(const PolymorphismSequenceContainer & ingroup, const PolymorphismSequenceContainer & outgroup , const GeneticCode & gc, double freqmin = 0);
    static double tajimaDSS(const PolymorphismSequenceContainer & psc, bool gapflag = true);
    static double tajimaDTNM(const PolymorphismSequenceContainer & psc, bool gapflag = true);
    static double fuliD(const PolymorphismSequenceContainer & ingroup, const PolymorphismSequenceContainer & outgroup);
    static double fuliDstar(const PolymorphismSequenceContainer & group);
    static double fuliF(const PolymorphismSequenceContainer & ingroup, const PolymorphismSequenceContainer & outgroup);
    static double fuliFstar(const PolymorphismSequenceContainer & group);
    static PolymorphismSequenceContainer * generateLDContainer(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);
    static Vdouble pairwiseDistances1(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static Vdouble pairwiseDistances2(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static Vdouble pairwiseD(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static Vdouble pairwiseDprime(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static Vdouble pairwiseR2(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static double meanD(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static double meanDprime(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static double meanR2(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static double meanDistance1(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static double meanDistance2(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static double originRegressionD(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static double originRegressionDprime(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static double originRegressionR2(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static Vdouble linearRegressionD(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static Vdouble linearRegressionDprime(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static Vdouble linearRegressionR2(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static double inverseRegressionR2(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0) throw (DimensionException);
    static double hudson87(const PolymorphismSequenceContainer & psc, double precision = 0.000001, double cinf=0.001, double csup=10000);
    static void testUsefullvalues(ostream & s, unsigned int n);
};
