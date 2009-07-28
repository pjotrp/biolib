%module bpptest
%{
#include "CodonAlphabet.h"
using namespace bpp;
%}
%include "AbstractAlphabet.i"
%include "NucleicAlphabet.i"
%include "std_string.i"
using namespace std;

class CodonAlphabet:public AbstractAlphabet
{
  public:
    static const string STOP;
    static const string INIT;

    CodonAlphabet(const NucleicAlphabet * alpha) : AbstractAlphabet(), nucAlpha(alpha);
    virtual ~CodonAlphabet();

    string getName(const string & state) const throw (BadCharException);
    int charToInt(const string & state) const throw (BadCharException);
    string getAlphabetType() const;
    int getUnknownCharacterCode() const; 
    bool isUnresolved(int state) const;
    bool isUnresolved(const string & state) const;
       
    virtual int getCodon(int pos1, int pos2, int pos3) const throw (BadIntException);
    virtual string getCodon(const string & pos1, const string & pos2, const string & pos3) const throw (BadCharException);
    virtual int getFirstPosition(int codon) const throw (BadIntException);
    virtual int getSecondPosition(int codon) const throw (BadIntException);
    virtual int getThirdPosition(int codon) const throw (BadIntException);
    virtual vector<int> getPositions(int codon) const throw (BadIntException);
    virtual string getFirstPosition (const string & codon) const throw (BadCharException);
    virtual string getSecondPosition(const string & codon) const throw (BadCharException);
    virtual string getThirdPosition(const string & codon) const throw (BadCharException);
    virtual vector<string> getPositions(const string & codon) const throw (BadCharException);
    virtual bool isStop(int codon) const = 0;
    virtual bool isStop(const string & codon) const = 0;
    virtual const NucleicAlphabet * getNucleicAlphabet() const;
};
