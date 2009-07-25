%module bpptest
%{
#include "PhredPhd.h"
using namespace bpp;
%}
%include "AbstractISequence.i"
%include "Sequence.i"
%include "SequenceContainer.i"
%include "VectorSequenceContainer.i"

class PhredPhd: public AbstractISequence {
  public:
    PhredPhd(double quality = 15, unsigned int lframe = 5, unsigned int rframe = 5);
    virtual ~PhredPhd();

    void appendFromStream(istream & input, VectorSequenceContainer & sc) const throw (Exception);
    const string getFormatName() const;
    const string getFormatDescription() const;
};
