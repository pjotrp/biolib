%module bpptest
%{
#include "Phylip.h"
using namespace bpp;
%}
%include "AbstractISequence2.i"
%include "AbstractOSequence.i"
%include "Sequence.i"
%include "SequenceContainer.i"
%include "VectorSequenceContainer.i"
%include "AlignedSequenceContainer.i"
%include "std_iostream.i"
using namespace std;

class Phylip:public virtual AbstractISequence2,public virtual AbstractOSequence
{
  public:
    Phylip(bool extended = true, bool sequential = true, unsigned int charsByLine = 100, bool checkNames = true, const string & split = "  "):
      _extended(extended), _sequential(sequential), _charsByLine(charsByLine), _checkNames(checkNames), _namesSplit(split);
    virtual ~Phylip();

    void appendFromStream(istream & input, AlignedSequenceContainer & sc) const throw (Exception);
    unsigned int getNumberOfSequences(const string & path) const throw (IOException);
    void write(ostream & output, const SequenceContainer & sc) const throw (Exception);
    void write(const string & path, const SequenceContainer & sc, bool overwrite) const throw (Exception);
    const string getFormatName() const;
    const string getFormatDescription() const;
    bool checkNames() const;
    void checkNames(bool yn);
    string getSplit() const;
    void setSplit(const string & split);
};
