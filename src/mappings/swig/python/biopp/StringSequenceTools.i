%module bpptest
%{
#include "StringSequenceTools.h"
using namespace bpp;
%}
%include "Alphabet.i"
%include "AlphabetExceptions.i"
%include "SequenceExceptions.i"
%include "Exceptions.i"
%include "std_string.i"
%include "std_vector.i"
using namespace std;

class StringSequenceTools
{
  public:
    StringSequenceTools();
     ~StringSequenceTools();

    static string subseq(const string & sequence, int begin, int end) throw (Exception);
    static string setToSizeR(const string & sequence, int size);
    static string setToSizeL(const string & sequence, int size);
    static string deleteChar(const string & sequence, char chars);
    static string deleteChar(const string & sequence, string chars);
    static string * reverse(const string & sequence);
    static string * complement(const string & sequence);
    static double getGCcontent(const string & sequence, unsigned int pos, unsigned int window) throw (BadIntegerException, Exception);
    static vector<int> codeSequence(const string & sequence, const Alphabet * alphabet) throw (BadCharException);
    static string decodeSequence(const vector<int> & sequence, const Alphabet * alphabet) throw (BadIntException);
    static Alphabet * getAlphabetFromSequence(const string sequence) throw (EmptySequenceException, SequenceException, AlphabetException);
};
