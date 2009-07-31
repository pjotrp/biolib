%module bpptest
%{
#include "SequenceSimulator.h"
using namespace bpp;
%}
%include "Clonable.i"
%include "SiteContainer.i"

%ignore SequenceSimulator::SequenceSimulator;
%ignore SequenceSimulator::~SequenceSimulator;

class SequenceSimulator:public virtual Clonable
{
  public:
    SequenceSimulator();
    virtual ~SequenceSimulator();
    SequenceSimulator * clone() const = 0;

    virtual SiteContainer * simulate(unsigned int numberOfSites) const = 0;
    virtual const Alphabet * getAlphabet() const = 0;  
};
