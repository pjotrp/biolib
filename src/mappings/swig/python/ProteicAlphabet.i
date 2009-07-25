%module bpptest
%{
#include "ProteicAlphabet.h"
using namespace bpp;
%}

%include "AbstractAlphabet.i"

class ProteicAlphabet:public AbstractAlphabet
{
  public:
    ProteicAlphabet();
    virtual ~ProteicAlphabet();

    unsigned int getSize() const;
    unsigned int getNumberOfTypes() const;
    int getUnknownCharacterCode() const;
     vector<int   > getAlias(      int      state) const throw (BadIntException);
    vector<string> getAlias(const string & state) const throw (BadCharException);
    int    getGeneric(const vector<int   > & states) const throw (BadIntException);
    string getGeneric(const vector<string> & states) const throw (BadCharException);
    bool isUnresolved(int state) const;
    bool isUnresolved(const string & state) const;
    string getAlphabetType() const;
    
    string getAbbr(const string & aa) const throw (AlphabetException);
    string getAbbr(int aa) const throw (AlphabetException);
};
