%module bpptest
%{
#include "DefaultAlphabet.h"
using namespace bpp;
%}
%include "AbstractAlphabet.i"

class DefaultAlphabet:public AbstractAlphabet
{
  public:
    DefaultAlphabet();
    virtual ~DefaultAlphabet();

    unsigned int getSize() const;
    unsigned int getNumberOfTypes() const;
    string getAlphabetType() const;
    int getUnknownCharacterCode() const;
    bool isUnresolved(int state) const;
    bool isUnresolved(const string & state) const;
};
