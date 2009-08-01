%module bpptest
%{
#include "SequenceTools.h"
using namespace bpp;
%}

%include "Alphabet.i"
%include "DNA.i"
%include "RNA.i"
%include "Sequence.i"
%include "SymbolListTools.i"
%include "NucleicAcidsReplication.i"
%include "RandomTools.i"
%include "StatTest.i"
%include "Exceptions.i"
%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"
//#include <algorithm>

using namespace std;

class BowkerTest:public StatTest
{
  public:
    BowkerTest();
    virtual ~BowkerTest();

    BowkerTest* clone() const;

    string getName() const;
    double getStatistic() const;
    double getPValue() const;

    void setStatistic(double stat);
    void setPValue(double pvalue);
};


%ignore SequenceTools::SequenceTools;
%ignore SequenceTools::~SequenceTools;

class SequenceTools:public SymbolListTools
{
  public:
    SequenceTools();
    virtual ~SequenceTools();
    static Sequence * subseq(const Sequence & sequence, unsigned int begin, unsigned int end) throw (IndexOutOfBoundsException, Exception) ;
    static Sequence * concatenate(const Sequence & seq1, const Sequence & seq2) throw (AlphabetMismatchException, Exception) ;
    static Sequence * complement(const Sequence & sequence) throw (AlphabetException);
    static Sequence * transcript(const Sequence & sequence) throw (AlphabetException);
    static Sequence * reverseTranscript(const Sequence & sequence) throw (AlphabetException);
    static Sequence * invert(const Sequence & sequence, bool chgSense = true);
    static Sequence * reverse(const Sequence & sequence);
    static double getPercentIdentity(const Sequence & seq1, const Sequence & seq2) throw (AlphabetMismatchException, SequenceNotAlignedException);
    static unsigned int getNumberOfSites(const Sequence & seq);
    static unsigned int getNumberOfCompleteSites(const Sequence & seq);
    static Sequence * removeGaps(const Sequence & seq);
    static BowkerTest* bowkerTest(const Sequence & seq1, const Sequence & seq2) throw (SequenceNotAlignedException);
    static Sequence * subtractHaplotype(const Sequence & s, const Sequence & h, string name = "", unsigned int level = 1) throw (SequenceNotAlignedException);
};
