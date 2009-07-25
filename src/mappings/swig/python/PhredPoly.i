%module bpptest
%{
#include "PhredPoly.h"
using namespace bpp;
%}
%include "AbstractISequence.i"
%include "Sequence.i"
%include "SequenceContainer.i"
%include "VectorSequenceContainer.i"

class PhredPoly: public AbstractISequence {
  public:
    PhredPoly(double ratio = 0.8);
    virtual ~PhredPoly();

    void appendFromStream(istream & input, VectorSequenceContainer & sc) const throw (Exception);
    const string getFormatName() const;
    const string getFormatDescription() const;
};
