%module bpptest
%{
#include "MarginalAncestralStateReconstruction.h"
using namespace bpp;
%}
%include "AncestralStateReconstruction.i"
%include "DRTreeLikelihood.i"
%include "Alphabet.i"
%include "AlignedSequenceContainer.i"
%include "Sequence.i"
%include "std_vector.i"
using namespace std;

class MarginalAncestralStateReconstruction:public AncestralStateReconstruction
{
  public:
    MarginalAncestralStateReconstruction(const DRTreeLikelihood & drl): _likelihood(& drl);
    virtual ~MarginalAncestralStateReconstruction();

    vector<int> getAncestralStatesForNode(int nodeId, VVdouble & probs, bool sample) const;
    vector<int> getAncestralStatesForNode(int nodeId) const;
    map<int, vector<int> > getAllAncestralStates() const;
    Sequence * getAncestralSequenceForNode(int nodeId, VVdouble * probs, bool sample) const;
    Sequence * getAncestralSequenceForNode(int nodeId) const;
    AlignedSequenceContainer *getAncestralSequences() const;
    AlignedSequenceContainer *getAncestralSequences(bool sample) const;
};
