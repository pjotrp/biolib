%module bpptest
%{
#include "DNA.h"
using namespace bpp;
%}
%include "NucleicAlphabet.i"
%include "std_string.i"
using namespace std;

//%rename(stringGetGeneric) DNA::getGeneric(vector<string>);
//%rename(stringGetGeneric) DNA::getGeneric(std::vector< std::string > const &);

class DNA:public NucleicAlphabet
{
    %rename(stringGetGeneric) getGeneric(const vector<string> & states) const throw (BadCharException);
  public:
    DNA();
    virtual ~DNA();

    vector<int   > getAlias(      int      state) const throw (BadIntException);
    vector<string> getAlias(const string & state) const throw (BadCharException);
    int    getGeneric(const vector<int   > & states) const throw (BadIntException);
    string getGeneric(const vector<string> & states) const throw (BadCharException);
    string getAlphabetType() const;
};

