%module bpptest
%{
#include "Alphabet.h"
using namespace bpp;
%}
%include "std_string.i"
%include "std_vector.i"
using namespace std;
%include "AlphabetExceptions.i"

class Alphabet
{
    %rename(stringGetGeneric) getGeneric(const vector<string> & states) const throw (AlphabetException);
  public:
    Alphabet();
    virtual ~Alphabet();

    virtual string getName(int state) const throw (BadIntException)  = 0;
    virtual string getName(const string & state) const throw (BadCharException) = 0;
    virtual bool isIntInAlphabet(int state) const = 0;
    virtual bool isCharInAlphabet(const string & state) const = 0;
    virtual string intToChar(int state) const throw (BadIntException) = 0;
    virtual int charToInt(const string & state) const throw (BadCharException) = 0;
    virtual unsigned int getNumberOfChars() const = 0;
    virtual unsigned int getNumberOfTypes() const = 0;
    virtual unsigned int getSize() const = 0;
    virtual vector<int> getAlias(int state) const throw (BadIntException) = 0;
    virtual vector<string> getAlias(const string & state) const throw (BadCharException) = 0;
    virtual int getGeneric(const vector<int> & states) const throw (BadIntException) = 0;
    virtual string getGeneric(const vector<string> & states) const throw (AlphabetException) = 0;
    virtual const vector<int> & getSupportedInts() const = 0;
    virtual const vector<string> & getSupportedChars() const = 0;
    virtual int getUnknownCharacterCode() const = 0;
    virtual int getGapCharacterCode() const = 0;
    virtual bool isGap(int state) const = 0;
    virtual bool isGap(const string & state) const = 0;
    virtual bool isUnresolved(int state) const = 0;
    virtual bool isUnresolved(const string & state) const = 0;
    virtual string getAlphabetType() const = 0;
};
