%module bpptest
%{
#include "NeighborJoining.h"
using namespace bpp;
%}
%include "AbstractAgglomerativeDistanceMethod.i"

%rename(__assign__) NeighborJoining::operator=;

class NeighborJoining :public AbstractAgglomerativeDistanceMethod
{
  public:
    NeighborJoining(): _positiveLengths(false);
    NeighborJoining(const DistanceMatrix & matrix, bool rooted=false, bool positiveLengths=false) throw (Exception);
    NeighborJoining(const NeighborJoining & nj): AbstractAgglomerativeDistanceMethod(nj), _sumDist(nj._sumDist), _positiveLengths(nj._positiveLengths);
    NeighborJoining & operator=(const NeighborJoining & nj);
    virtual ~NeighborJoining();

    virtual void setDistanceMatrix(const DistanceMatrix & matrix);
    virtual void outputPositiveLengths(bool yn);

  protected:
    //virtual vector<unsigned int> getBestPair() throw (Exception);
    //virtual vector<double> computeBranchLengthsForPair(const vector<unsigned int> & pair);
    //virtual double computeDistancesFromPair(const vector<unsigned int> & pair, const vector<double> & branchLengths, unsigned int pos);
    //virtual void finalStep(int idRoot);  
};
