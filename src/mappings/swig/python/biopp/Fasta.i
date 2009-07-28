%module bpptest
%{
#include "Fasta.h"
using namespace bpp;
%}
%include "AbstractISequence.i"
%include "AbstractOSequence.i"
%include "Sequence.i"
%include "SequenceContainer.i"
%include "VectorSequenceContainer.i"

class Fasta:public virtual AbstractISequence,public virtual AbstractOSequence
{
  public:
    Fasta(unsigned int charsByLine = 100, bool checkNames = true, bool extended = false): _charsByLine(charsByLine), _checkNames(checkNames), _extended(extended);
    virtual ~Fasta();

    void appendFromStream(istream & input, VectorSequenceContainer & sc) const throw (Exception);
    void write(ostream & output, const SequenceContainer & sc) const throw (Exception);
    void write(const string & path, const SequenceContainer & sc, bool overwrite=true) const throw (Exception);
    const string getFormatName() const;
    const string getFormatDescription() const;
    bool checkNames() const;
    void checkNames(bool yn);
};
