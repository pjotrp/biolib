%module bpptest
%{
#include "Mase.h"
using namespace bpp;
%}

%include "AbstractISequence.i"
%include "AbstractOSequence.i"
%include "Sequence.i"
%include "SequenceContainer.i"
%include "VectorSequenceContainer.i"

class Mase:public virtual AbstractISequence,public virtual AbstractOSequence
{
  public :
    Mase(unsigned int charsByLine = 100, bool checkNames = true): _charsByLine(charsByLine), _checkNames(checkNames);
    virtual ~Mase();

    void appendFromStream(istream & input, VectorSequenceContainer & sc) const throw (Exception);
    void write(ostream & output, const SequenceContainer & sc) const throw (Exception);
    void write(const string & path, const SequenceContainer & sc, bool overwrite = true) const throw (Exception);
    const string getFormatName() const;
    const string getFormatDescription() const;
    bool checkNames() const;
    void checkNames(bool yn);
};

