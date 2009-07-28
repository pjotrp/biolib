%module bpptest
%{
#include "UserProteinSubstitutionModelF.h"
using namespace bpp;
%}
%include "ProteinSubstitutionModelWithFrequencies.i"
%include "ProteicAlphabet.i"
%include "std_string.i"
using namespace std;

class UserProteinSubstitutionModelF:public ProteinSubstitutionModelWithFrequencies
{
  public:
    UserProteinSubstitutionModelF(const ProteicAlphabet * alpha, const string & path, const string& prefix);
    virtual ~UserProteinSubstitutionModelF();
    UserProteinSubstitutionModelF* clone() const;

    string getName() const;
    const string & getPath() const;
};
