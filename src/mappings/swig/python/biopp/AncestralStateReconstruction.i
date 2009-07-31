%module bpptest
%{
#include "AncestralStateReconstruction.h"
using namespace bpp;
%}
%include "Sequence.i"
%include "SequenceContainer.i"
%include "std_vector.i"
%include "std_map.i"
using namespace std;

class Node;

%ignore AncestralStateReconstruction::AncestralStateReconstruction;
%ignore AncestralStateReconstruction::~AncestralStateReconstruction;

class AncestralStateReconstruction
{
  public:
    AncestralStateReconstruction();
    virtual ~AncestralStateReconstruction();

    virtual vector<int> getAncestralStatesForNode(int nodeId) const = 0;
    virtual map<int, vector<int> > getAllAncestralStates() const = 0;
    virtual Sequence * getAncestralSequenceForNode(int nodeId) const = 0;
    virtual SequenceContainer * getAncestralSequences() const = 0;
};
