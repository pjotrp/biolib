%module bpptest
%{
#include "UserProteinSubstitutionModel.h"
using namespace bpp;
%}
%include "ProteinSubstitutionModel.i"
%include "ProteicAlphabet.i"
%include "std_string.i"
using namespace std;

class UserProteinSubstitutionModel:public ProteinSubstitutionModel
{
  public:
    UserProteinSubstitutionModel(const ProteicAlphabet * alpha, const string & path, const string& prefix);
    virtual ~UserProteinSubstitutionModel();
    UserProteinSubstitutionModel* clone() const;

    string getName() const;
    const string & getPath() const;
};
