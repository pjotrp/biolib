%module bpptest
%{
#include "RNA.h"
using namespace bpp;
%}
%include "NucleicAlphabet.i"
%include "std_string.i"
using namespace std;

class RNA:public NucleicAlphabet
{
    %rename(stringGetGeneric) getGeneric(const vector<string> & states) const throw (BadCharException);
  public:
    RNA();
    ~RNA();

    vector<int   > getAlias(      int      state) const throw (BadIntException);
    vector<string> getAlias(const string & state) const throw (BadCharException);
    int    getGeneric(const vector<int   > & states) const throw (BadIntException);
    string getGeneric(const vector<string> & states) const throw (BadCharException);
    string getAlphabetType() const;
};
