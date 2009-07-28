%module bpptest
%{
#include "AlphabetTools.h"
using namespace bpp;
%}
#include "alphabets"
#include <typeinfo>
%include "VectorTools.i"

class AlphabetTools
{
  public:
    static const DNA DNA_ALPHABET;
    static const RNA RNA_ALPHABET;
    static const ProteicAlphabet PROTEIN_ALPHABET;
    static const DefaultAlphabet DEFAULT_ALPHABET;

    AlphabetTools();
    virtual ~AlphabetTools();

    static int getType(char state);
    static bool checkAlphabetCodingSize(const Alphabet & alphabet) throw (AlphabetException);
    static bool checkAlphabetCodingSize(const Alphabet * alphabet) throw (AlphabetException);
    static int getAlphabetCodingSize(const Alphabet & alphabet) throw (AlphabetException);
    static int getAlphabetCodingSize(const Alphabet * alphabet) throw (AlphabetException);
    static bool isNucleicAlphabet(const Alphabet * alphabet);
    static bool isDNAAlphabet(const Alphabet * alphabet);
    static bool isRNAAlphabet(const Alphabet * alphabet);
    static bool isProteicAlphabet(const Alphabet * alphabet);
    static bool isCodonAlphabet(const Alphabet * alphabet);
    static bool isDefaultAlphabet(const Alphabet * alphabet);
    static bool match(const Alphabet * alphabet, int i, int j);
};
