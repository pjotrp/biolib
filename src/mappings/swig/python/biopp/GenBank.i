%module bpptest
%{
#include "GenBank.h"
using namespace bpp;
%}
%include "AbstractISequence.i"
%include "Sequence.i"
%include "SequenceContainer.i"
%include "VectorSequenceContainer.i"

class GenBank:public AbstractISequence
{
  public:
    GenBank();
    virtual ~GenBank();

    void appendFromStream(istream & input, VectorSequenceContainer & sc) const throw (Exception);
    const string getFormatName() const;
    const string getFormatDescription() const;
};
