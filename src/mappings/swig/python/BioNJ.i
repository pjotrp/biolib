%module bpptest
%{
#include "BioNJ.h"
using namespace bpp;
%}
%include "NeighborJoining.i"

%rename(__assign__) BioNJ::operator=;

class BioNJ:public NeighborJoining
{
  public:
    BioNJ();
    BioNJ(const DistanceMatrix & matrix, bool rooted = false, bool positiveLengths = false) throw (Exception);
    BioNJ(const BioNJ & bionj);
    BioNJ & operator=(const BioNJ & bionj);
    virtual ~BioNJ();

    virtual void setDistanceMatrix(const DistanceMatrix & matrix);
    virtual void computeTree(bool rooted) throw (Exception);
    virtual double computeDistancesFromPair(const vector<unsigned int> & pair, const vector<double> & branchLengths, unsigned int pos);
};
