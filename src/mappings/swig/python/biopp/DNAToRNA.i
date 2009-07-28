%module bpptest
%{
#include "DNAToRNA.h"
using namespace bpp;
%}
%include "Translator.i"
%include "DNA.i"
%include "RNA.i"

class DNAToRNA:public AbstractReverseTranslator
{
  public:
    DNAToRNA();
    virtual ~DNAToRNA();

    virtual const Alphabet * getSourceAlphabet() const;
    virtual const Alphabet * getTargetAlphabet() const;
    int translate(int state) const throw (BadIntException);    
    string translate(const string & state) const throw (BadCharException);    
    Sequence * translate(const Sequence& sequence) const throw (AlphabetMismatchException, Exception);
    int reverse(int state) const throw (BadIntException);
    string reverse(const string & state) const throw (BadCharException);
    Sequence * reverse(const Sequence& sequence) const throw (AlphabetMismatchException, Exception);
};
