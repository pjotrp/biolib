%module bpptest
%{
#include "AbstractAlphabet.h"
using namespace bpp;
%}
%include "Alphabet.i"
%include "Exceptions.i"
using namespace std;

class AbstractAlphabet:public Alphabet
{
  public:
    AbstractAlphabet();
    virtual ~AbstractAlphabet();

    unsigned int getNumberOfChars() const;
    string getName(const string & state) const throw (BadCharException);
    string getName(int state) const throw (BadIntException);
    int charToInt(const string & state) const throw (BadCharException);
    string intToChar(int state) const throw (BadIntException);
    bool isIntInAlphabet(int state) const;
    bool isCharInAlphabet(const string & state) const;
    vector<int> getAlias(int state) const throw (BadIntException);
    vector<string> getAlias(const string & state) const throw (BadCharException);
    int    getGeneric(const vector<int   > & states) const throw (BadIntException);
    string getGeneric(const vector<string> & states) const throw (AlphabetException);
    const vector<int> & getSupportedInts() const;
    const vector<string> & getSupportedChars() const;
    int getGapCharacterCode() const;
    bool isGap(int state) const;
    bool isGap(const string & state) const;
};
