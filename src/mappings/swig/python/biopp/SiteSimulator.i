%module bpptest
%{
#include "SiteSimulator.h"
using namespace bpp;
%}
%include "Site.i"

class SiteSimulator
{
  public:
    SiteSimulator();
    virtual ~SiteSimulator();

    virtual Site * simulate() const = 0;
    virtual Site * simulate(int ancestralState) const = 0;
    virtual Site * simulate(int ancestralState, double rate) const = 0;
    virtual Site * simulate(double rate) const = 0;
    virtual vector<string> getSequencesNames() const = 0;
    virtual const Alphabet * getAlphabet() const = 0;
};
