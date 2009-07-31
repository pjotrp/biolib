%module bpptest
%{
#include "OptimizationTools.h"
using namespace bpp;
%}
%include "ClockTreeLikelihood.i"
%include "NNIHomogeneousTreeLikelihood.i"
%include "ClockTreeLikelihood.i"
%include "NNITopologySearch.i"
%include "DRTreeParsimonyScore.i"
%include "TreeTemplate.i"
%include "DistanceEstimation.i"
%include "AgglomerativeDistanceMethod.i"
%include "SimpleNewtonMultiDimensions.i"
%include "std_iostream.i"
using namespace std;

class NNITopologyListener:public TopologyListener
{
  public:
    NNITopologyListener(NNITopologySearch * ts, const ParameterList& parameters, double tolerance, ostream *messenger, ostream *profiler, unsigned int verbose, const string & optMethod, unsigned int nStep);
    virtual ~NNITopologyListener();

    void topologyChangeTested(const TopologyChangeEvent & event);
    void topologyChangeSuccessful(const TopologyChangeEvent & event);
    void setNumericalOptimizationCounter(unsigned int c);
};

class NNITopologyListener2:public TopologyListener
{
  public:
    NNITopologyListener2(NNITopologySearch * ts, const ParameterList& parameters, double tolerance, ostream *messenger, ostream *profiler, unsigned int verbose, const string & optMethod);
    virtual ~NNITopologyListener2();

    void topologyChangeTested(const TopologyChangeEvent & event);
    void topologyChangeSuccessful(const TopologyChangeEvent & event);
    void setNumericalOptimizationCounter(unsigned int c);
};

%ignore OptimizationTools::OptimizationTools;
%ignore OptimizationTools::~OptimizationTools;

class OptimizationTools
{
  public:
    OptimizationTools();
    virtual ~OptimizationTools();

    static string OPTIMIZATION_GRADIENT;
    static string OPTIMIZATION_NEWTON;
    static unsigned int optimizeNumericalParameters(DiscreteRatesAcrossSitesTreeLikelihood * tl,const ParameterList& parameters,OptimizationListener * listener = NULL,unsigned int nstep = 1,double tolerance = 0.000001,unsigned int tlEvalMax = 1000000,ostream * messageHandler = &cout,ostream * profiler       = &cout,unsigned int verbose = 1,const string & method = OPTIMIZATION_NEWTON)throw (Exception);
    static unsigned int optimizeNumericalParameters2(DiscreteRatesAcrossSitesTreeLikelihood * tl,const ParameterList& parameters,OptimizationListener * listener = NULL,double tolerance = 0.000001,unsigned int tlEvalMax = 1000000,ostream * messageHandler = &cout,ostream * profiler       = &cout,unsigned int verbose = 1,const string & optMethod = OPTIMIZATION_NEWTON)throw (Exception);
    static unsigned int optimizeBranchLengthsParameters(DiscreteRatesAcrossSitesTreeLikelihood * tl,const ParameterList& parameters,OptimizationListener * listener = NULL,double tolerance = 0.000001,unsigned int tlEvalMax = 1000000,ostream * messageHandler = &cout,ostream * profiler       = &cout,unsigned int verbose = 1,const string & optMethod = OPTIMIZATION_NEWTON)throw (Exception);
    static unsigned int optimizeNumericalParametersWithGlobalClock(DiscreteRatesAcrossSitesClockTreeLikelihood * cl,const ParameterList& parameters,OptimizationListener * listener = NULL,unsigned int nstep = 1,double tolerance = 0.000001,unsigned int tlEvalMax = 1000000,ostream * messageHandler = &cout,ostream * profiler       = &cout,unsigned int verbose = 1,const string & optMethod = OPTIMIZATION_GRADIENT)throw (Exception);
    static unsigned int optimizeNumericalParametersWithGlobalClock2(DiscreteRatesAcrossSitesClockTreeLikelihood * cl,const ParameterList& parameters,OptimizationListener * listener = NULL,double tolerance = 0.000001,unsigned int tlEvalMax = 1000000,ostream * messageHandler = &cout,ostream * profiler       = &cout,unsigned int verbose = 1,const string & optMethod = OPTIMIZATION_GRADIENT)throw (Exception);

    static unsigned int optimizeTreeScale( TreeLikelihood * tl, double tolerance = 0.000001, int tlEvalMax = 1000000, ostream * messageHandler = &cout, ostream * profiler = &cout, unsigned int verbose = 1)throw (Exception);
    static NNIHomogeneousTreeLikelihood * optimizeTreeNNI( NNIHomogeneousTreeLikelihood * tl, const ParameterList& parameters, bool optimizeNumFirst = true, double tolBefore = 100, double tolDuring = 100, int tlEvalMax = 1000000, unsigned int numStep = 1, ostream * messageHandler = &cout, ostream * profiler = &cout, unsigned int verbose = 1, const string & optMethod = OptimizationTools::OPTIMIZATION_NEWTON, unsigned int nStep = 1, const string & nniMethod = NNITopologySearch::PHYML)throw (Exception);
    static NNIHomogeneousTreeLikelihood * optimizeTreeNNI2( NNIHomogeneousTreeLikelihood * tl, const ParameterList& parameters, bool optimizeNumFirst = true, double tolBefore = 100, double tolDuring = 100, int tlEvalMax = 1000000, unsigned int numStep = 1, ostream * messageHandler = &cout, ostream * profiler = &cout, unsigned int verbose = 1, const string & optMethod = OptimizationTools::OPTIMIZATION_NEWTON, const string & nniMethod = NNITopologySearch::PHYML)throw (Exception);
    static DRTreeParsimonyScore * optimizeTreeNNI( DRTreeParsimonyScore * tp, unsigned int verbose = 1);
    static TreeTemplate<Node> * buildDistanceTree( DistanceEstimation & estimationMethod, AgglomerativeDistanceMethod & reconstructionMethod, const ParameterList & parametersToIgnore, bool optimizeBrLen = false, bool rooted = false, const string & param = DISTANCEMETHOD_INIT, double tolerance = 0.000001, unsigned int tlEvalMax = 1000000, ostream * profiler = NULL, ostream * messenger = NULL, unsigned int verbose = 0) throw (Exception);

    static string DISTANCEMETHOD_INIT;
    static string DISTANCEMETHOD_PAIRWISE;
    static string DISTANCEMETHOD_ITERATIONS;
};
