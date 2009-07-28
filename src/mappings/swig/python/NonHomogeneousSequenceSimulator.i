%module bpptest
%{
#include "NonHomogeneousSequenceSimulator.h"
using namespace bpp;
%}
%include "DetailedSiteSimulator.i"
%include "SequenceSimulator.i"
%include "TreeTemplate.i"
%include "NodeTemplate.i"
%include "SubstitutionModel.i"
%include "Alphabet.i"
%include "Site.i"
%include "SiteContainer.i"
%include "DiscreteDistribution.i"
%include "RandomTools.i"
%include "std_map.i"
%include "std_vector.i"
using namespace std;
%include "SubstitutionModelSet.i"

class SimData
{
  public:
    int state;
    vector<int> states;
    VVVdouble cumpxy;
    const SubstitutionModel* model;
};

typedef NodeTemplate<SimData> SNode;

class NonHomogeneousSequenceSimulator:public DetailedSiteSimulator,public SequenceSimulator
{
  public:    
    NonHomogeneousSequenceSimulator(const SubstitutionModelSet * modelSet,const DiscreteDistribution * rate,const TreeTemplate<Node> * tree) throw (Exception);
    NonHomogeneousSequenceSimulator(const SubstitutionModel * model,const DiscreteDistribution * rate,const TreeTemplate<Node> * tree);
    virtual ~NonHomogeneousSequenceSimulator();

    NonHomogeneousSequenceSimulator *clone() const;

    Site * simulate() const;
    Site * simulate(int ancestralState) const;
    Site * simulate(int ancestralState, double rate) const;
    Site * simulate(double rate) const;
    vector<string> getSequencesNames() const;
    RASiteSimulationResult * dSimulate() const;
    RASiteSimulationResult * dSimulate(int ancestralState) const;
    RASiteSimulationResult * dSimulate(int ancestralState, double rate) const;
    RASiteSimulationResult * dSimulate(double rate) const;
    SiteContainer * simulate(unsigned int numberOfSites) const;
    const Alphabet * getAlphabet() const;
    virtual Site * simulate(int ancestralState, unsigned int rateClass) const;
    virtual  RASiteSimulationResult * dSimulate(int ancestralState, unsigned int rateClass) const;
    const SubstitutionModelSet * getSubstitutionModelSet() const;
    const DiscreteDistribution * getRateDistribution() const;
    const TreeTemplate<Node> * getTree() const;
    void enableContinuousRates(bool yn);
};
