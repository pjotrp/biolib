%module bpptest
%{
#include "HomogeneousSequenceSimulator.h"
using namespace bpp;
%}
%include "NonHomogeneousSequenceSimulator.i"

class HomogeneousSequenceSimulator:public NonHomogeneousSequenceSimulator
{
  public:
    HomogeneousSequenceSimulator(const SubstitutionModel * model, const DiscreteDistribution * rate, const TreeTemplate<Node> * tree);
    virtual ~HomogeneousSequenceSimulator();

    const SubstitutionModel* getSubstitutionModel() const;
};
