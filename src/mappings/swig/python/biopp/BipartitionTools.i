%module bpptest
%{
#include "BipartitionTools.h"
using namespace bpp;
%}
%include "BipartitionList.i"
%include "VectorSiteContainer.i"

class BipartitionTools
{
  public:
    static unsigned int LWORD;

    BipartitionTools();
    virtual ~BipartitionTools();

    static void bit1(int *list, int num);
    static void bit0(int *list, int num);
    static void bitAnd(int *listet, int *list1, int *list2, unsigned int len);
    static void bitOr(int *listou, int *list1, int *list2, unsigned int len);
    static void bitNot(int *listnon, int *list, unsigned int len);
    static bool testBit(int *list, int num);
    static BipartitionList* mergeBipartitionLists(const vector<BipartitionList *> & vecBipartL, bool checkElements = true) throw (Exception);
    static BipartitionList* buildBipartitionPair(const BipartitionList & bipartL1, unsigned int i1, const BipartitionList & bipartL2, unsigned int i2, bool checkElements = true) throw (Exception);
    static bool areIdentical(const BipartitionList & bipart1, unsigned int i1, const BipartitionList & bipart2, unsigned int i2, bool checkElements = true);
    static bool areCompatible(const BipartitionList & bipart1, unsigned int i1, const BipartitionList & bipart2, unsigned int i2, bool checkElements = true);
    static VectorSiteContainer* MRPEncode(const vector<BipartitionList *> & vecBipartL) throw (Exception);
};
