%module bpptest
%{
#include "Translator.h"
using namespace bpp;
%}
%include "Alphabet.i"
%include "Sequence.i"

class Translator
{
  public:
    Translator();
    virtual ~Translator();

    virtual const Alphabet * getSourceAlphabet() const = 0;
    virtual const Alphabet * getTargetAlphabet() const = 0;
    virtual int translate(int state) const throw (BadIntException, Exception) = 0;    
    virtual string translate(const string & state) const throw (BadCharException, Exception) = 0;
    virtual Sequence * translate(const Sequence & sequence) const throw (AlphabetMismatchException, Exception) = 0; 
};

class ReverseTranslator:public virtual Translator
{
  public:
    ReverseTranslator();
    virtual ~ReverseTranslator();

    virtual int reverse(int state) const throw (BadIntException, Exception) = 0;
    virtual string reverse(const string & state) const throw (BadCharException, Exception) = 0;      
    virtual Sequence * reverse(const Sequence & sequence) const throw (AlphabetMismatchException, Exception) = 0; 
};

class AbstractTranslator:public virtual Translator
{
  public:
    AbstractTranslator();
    virtual ~AbstractTranslator();

    virtual int translate(int state) const throw (BadIntException, Exception) = 0;    
    virtual string translate(const string & state) const throw (BadCharException, Exception) = 0;
    virtual Sequence * translate(const Sequence & sequence) const throw (AlphabetMismatchException, Exception); 
};

class AbstractReverseTranslator:public ReverseTranslator,public AbstractTranslator
{
  public:
    AbstractReverseTranslator();
    virtual ~AbstractReverseTranslator();

    virtual const Alphabet * getSourceAlphabet() const = 0;
    virtual const Alphabet * getTargetAlphabet() const = 0;
    virtual int reverse(int state) const throw (BadIntException, Exception) = 0;
    virtual string reverse(const string & state) const throw (BadCharException, Exception) = 0;      
    virtual Sequence * reverse(const Sequence & sequence) const throw (AlphabetMismatchException, Exception);
};

