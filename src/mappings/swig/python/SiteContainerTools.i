%module bpptest
%{
#include "SiteContainerTools.h"
using namespace bpp;
%}
%include "SiteContainer.i"
%include "VectorSiteContainer.i"
%include "AlignedSequenceContainer.i"
%include "AlphabetIndex2.i"
%include "DistanceMatrix.i"
%include "std_vector.i"
%include "std_map.i"
using namespace std;
%include "Matrix.i"

typedef vector<unsigned int> SiteSelection;
class SiteContainerTools
{
  public:
    SiteContainerTools();
    virtual ~SiteContainerTools();

    static SiteContainer * getSitesWithoutGaps(const SiteContainer & sites);
    static SiteContainer * getCompleteSites(const SiteContainer & sites);
    static SiteContainer * removeGapOnlySites(const SiteContainer & sites);
    static SiteContainer * removeGapOrUnresolvedOnlySites(const SiteContainer & sites);
    static SiteContainer * getSelectedSites(const SiteContainer & sequences, const SiteSelection & selection);
    static const Sequence * getConsensus(const SiteContainer & sc,string name="consensus", bool ignoreGap = true, bool resolveUnknown = false);
    static void changeGapsToUnknownCharacters(SiteContainer & sites);
    static void changeUnresolvedCharactersToGaps(SiteContainer & sites);
    static SiteContainer * resolveDottedAlignment(const SiteContainer & dottedAln, const Alphabet * resolvedAlphabet) throw (AlphabetException, Exception);
    static map<unsigned int, unsigned int> getSequencePositions(const Sequence & seq);
    static map<unsigned int, unsigned int> getAlignmentPositions(const Sequence & seq);
    static map<unsigned int, unsigned int> translateAlignment(const Sequence & seq1, const Sequence & seq2) throw (AlphabetMismatchException, Exception);
    static map<unsigned int, unsigned int> translateSequence(const SiteContainer & sequences, unsigned int i1, unsigned int i2);
    static AlignedSequenceContainer * alignNW(const Sequence & seq1, const Sequence & seq2, const AlphabetIndex2<double> & s, double gap) throw (AlphabetMismatchException);
    static AlignedSequenceContainer * alignNW(const Sequence & seq1, const Sequence & seq2, const AlphabetIndex2<double> & s, double opening, double extending) throw (AlphabetMismatchException);
    static VectorSiteContainer * bootstrapSites(const SiteContainer & sites);
    static double computeSimilarity(const Sequence & seq1, const Sequence & seq2, bool dist = false, const string & gapOption = SIMILARITY_NODOUBLEGAP, bool unresolvedAsGap = true) throw (SequenceNotAlignedException, AlphabetMismatchException, Exception);
    static DistanceMatrix * computeSimilarityMatrix(const SiteContainer & sites, bool dist = false, const string & gapOption = SIMILARITY_NOFULLGAP, bool unresolvedAsGap = true);
    static const string SIMILARITY_ALL;
    static const string SIMILARITY_NOFULLGAP;
    static const string SIMILARITY_NODOUBLEGAP;
    static const string SIMILARITY_NOGAP;
};
