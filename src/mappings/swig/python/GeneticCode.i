%module bpptest
%{
#include "GeneticCode.h"
using namespace bpp;
%}
%include "Translator.i"
%include "CodonAlphabet.i"
%include "ProteicAlphabet.i"
%include "Exceptions.i"

class StopCodonException:public Exception
{
  public:
    StopCodonException(const string & text, const string & codon);
    virtual ~StopCodonException() throw ();

    virtual string getCodon() const;
};

class GeneticCode:public AbstractTranslator
{
  public:
    GeneticCode(): AbstractTranslator();
    virtual ~GeneticCode();

    const Alphabet * getSourceAlphabet() const;
    const Alphabet * getTargetAlphabet() const;
    virtual int translate(int state) const throw (BadIntException, Exception)  = 0;    
    virtual string translate(const string & state) const throw (BadCharException, Exception) = 0;
    virtual Sequence * translate(const Sequence & sequence) const throw (Exception);
    bool areSynonymous(int i, int j) const throw (BadIntException);
    bool areSynonymous(const string & i, const string & j) const throw (BadCharException);
    vector<int> getSynonymous(int aminoacid) const throw (BadIntException);
    vector<string> getSynonymous(const string & aminoacid) const throw (BadCharException);
    Sequence * getCodingSequence(const Sequence & sequence, bool lookForInitCodon = false, bool includeInitCodon = false) const throw (Exception);
};
