%module bpptest
%{
#include "DetailedSiteSimulator.h"
using namespace bpp;
%}
%include "SiteSimulator.i"
%include "TreeTemplate.i"
%include "MutationProcess.i"
%include "std_map.i"
%include "std_vector.i"
using namespace std;

class SiteSimulationResult
{
  public:
    SiteSimulationResult(const Tree * tree, const Alphabet * alphabet, int ancestralState);
    virtual ~SiteSimulationResult();

    virtual const Alphabet * getAlphabet() const;
    virtual void addNode(int nodeId, MutationPath path);
    virtual int getAncestralState(unsigned int i) const;
    virtual int getAncestralState(int nodeId) const;
    virtual unsigned int getSubstitutionCount(unsigned int i) const;
    virtual unsigned int getSubstitutionCount(int nodeId) const;
    virtual vector<double> getSubstitutionVector() const;
    virtual vector<int> getFinalStates() const;
    virtual Site * getSite() const;
    virtual vector<string> getLeaveNames() const;
};

class RASiteSimulationResult:public SiteSimulationResult
{
  public:
    RASiteSimulationResult(const Tree* tree, const Alphabet * alphabet, int ancestralState, double rate);
    virtual ~RASiteSimulationResult();

    virtual double getRate() const;
};

class DetailedSiteSimulator:public virtual SiteSimulator
{
  public:
    DetailedSiteSimulator();
    virtual ~DetailedSiteSimulator();

    virtual SiteSimulationResult * dSimulate() const = 0;
    virtual SiteSimulationResult * dSimulate(int ancestralState) const = 0;
    virtual SiteSimulationResult * dSimulate(int ancestralState, double rate) const = 0;
    virtual SiteSimulationResult * dSimulate(double rate) const = 0;
};
