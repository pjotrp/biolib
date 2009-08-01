%module bpptest
%{
#include "SymbolListTools.h"
using namespace bpp;
%}
%include "SymbolList.i"
%include "AlphabetExceptions.i"
%include "VectorExceptions.i"
%include "std_map.i"
using namespace std;

%ignore SymbolListTools::SymbolListTools;
%ignore SymbolListTools::~SymbolListTools;

class SymbolListTools
{
  public: 
    SymbolListTools();
    virtual ~SymbolListTools();

    static void getCounts(const SymbolList & list,  map<int, unsigned int> & counts);
    static void getCounts(const SymbolList & list1, const SymbolList & list2, map<int, map<int, unsigned int> > & counts) throw (DimensionException);
    static void getCounts(const SymbolList & list,  map<int, double> & counts, bool resolveUnknowns);
    static void getCounts(const SymbolList & list1, const SymbolList & list2,  map< int, map<int, double> > & counts, bool resolveUnknowns) throw (DimensionException);
    static void getFrequencies(const SymbolList & list, map<int, double> & frequencies, bool resolveUnknowns = false);
    static void getFrequencies(const SymbolList & list1, const SymbolList & list2, map<int, map<int, double> > & frequencies, bool resolveUnknowns = false) throw (DimensionException);
    static double getGCContent(const SymbolList & list, bool ignoreUnresolved = true, bool ignoreGap = true) throw (AlphabetException);
    static unsigned int getNumberOfDistinctPositions(const SymbolList & l1, const SymbolList & l2) throw (AlphabetMismatchException);
    static unsigned int getNumberOfPositionsWithoutGap(const SymbolList & l1, const SymbolList & l2) throw (AlphabetMismatchException);
    static void changeGapsToUnknownCharacters(SymbolList & l);
    static void changeUnresolvedCharactersToGaps(SymbolList & l);
    static void randomizeContent(SymbolList & l);
};
