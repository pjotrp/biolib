%module bpptest
%{
#include "SequenceSimulationTools.h"
using namespace bpp;
%}
%include "SiteSimulator.i"
%include "SiteContainer.i"
%include "std_vector.i"

class SequenceSimulationTools
{
  public:
    SequenceSimulationTools();
    ~SequenceSimulationTools();

    static SiteContainer * simulateSites(const SiteSimulator & simulator, const vector<double> & rates);
    static SiteContainer * simulateSites(const SiteSimulator & simulator, const vector<double> & rates, const vector<int> & states) throw (Exception);
};
