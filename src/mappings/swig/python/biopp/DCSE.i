%module bpptest
%{
#include "DCSE.h"
using namespace bpp;
%}
%include "AbstractISequence2.i"
%include "Sequence.i"
%include "SequenceContainer.i"
%include "AlignedSequenceContainer.i"

class DCSE : public virtual AbstractISequence2
{
  public: 
    DCSE();
    virtual ~DCSE();

    void appendFromStream(istream & input, AlignedSequenceContainer & sc) const throw (Exception);
    const string getFormatName() const;
    const string getFormatDescription() const;
};
