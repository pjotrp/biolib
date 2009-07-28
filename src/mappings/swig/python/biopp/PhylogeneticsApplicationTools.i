%module bpptest
%{
#include "PhylogeneticsApplicationTools.h"
using namespace bpp;
%}
%include "Tree.i"
%include "SubstitutionModel.i"
%include "SubstitutionModelSet.i"
%include "MarkovModulatedSubstitutionModel.i"
%include "HomogeneousTreeLikelihood.i"
%include "ClockTreeLikelihood.i"
%include "TextTools.i"
%include "StringTokenizer.i"
%include "DiscreteDistribution.i"
%include "SiteContainer.i"
%include "VectorSiteContainer.i"
%include "std_string.i"
%include "std_map.i"
%include "std_iostream.i"
using namespace std;

class PhylogeneticsApplicationTools
{
  public:
    PhylogeneticsApplicationTools();
    virtual ~PhylogeneticsApplicationTools();
    static TreeTemplate<Node> * getTree(map<string, string> & params,const string & suffix = "",bool suffixIsOptional = true,bool verbose = true) throw (Exception);
    static void printInputTreeHelp();
    static SubstitutionModel * getSubstitutionModelDefaultInstance(const Alphabet* alphabet,const string& modelDescription,map<string, string>& unparsedParameterValues,bool allowCovarions,bool allowGaps,bool verbose) throw (Exception);
    static void setSubstitutionModelParametersInitialValues(SubstitutionModel* model,map<string, string>& unparsedParameterValues,const SiteContainer* data,bool verbose) throw (Exception);
    static SubstitutionModel * getSubstitutionModel(const Alphabet* alphabet,const SiteContainer* data, map<string, string>& params,const string & suffix = "",bool suffixIsOptional = true,bool verbose = true) throw (Exception);
    static void setSubstitutionModelParametersInitialValues(SubstitutionModel* model,map<string, string>& unparsedParameterValues,const string& modelPrefix,const SiteContainer* data,map<string, double>& existingParams,vector<string>& specificParams,vector<string>& sharedParams,bool verbose) throw (Exception);
    static FrequenciesSet * getFrequenciesSet(const Alphabet * alphabet,const SiteContainer * data, map<string, string> & params,const vector<double> & rateFreqs,const string & suffix = "",bool suffixIsOptional = true,bool verbose = true) throw (Exception);
    static SubstitutionModelSet * getSubstitutionModelSet(const Alphabet * alphabet,const SiteContainer * data, map<string, string> & params,const string & suffix = "",bool suffixIsOptional = true,bool verbose = true) throw (Exception);
    static DiscreteDistribution* getRateDistributionDefaultInstance(const string& distDescription,map<string, string>& unparsedParameterValues,bool constDistAllowed = true,bool verbose = true) throw (Exception);
    static void setRateDistributionParametersInitialValues(DiscreteDistribution * rDist,map<string, string> & unparsedParameterValues,bool verbose = true) throw (Exception);
    static DiscreteDistribution * getRateDistribution(map<string, string> & params,const string & suffix = "",bool suffixIsOptional = true,bool verbose = true) throw (Exception);
    static TreeLikelihood* optimizeParameters(TreeLikelihood* tl,const ParameterList& parameters,map<string, string>& params,const string& suffix = "",bool suffixIsOptional = true,bool verbose = true) throw (Exception);
    static void optimizeParameters(DiscreteRatesAcrossSitesClockTreeLikelihood * tl,const ParameterList& parameters,map<string, string> & params,const string & suffix = "",bool suffixIsOptional = true,bool verbose = true) throw (Exception);
    static void printOptimizationHelp(bool topo = true, bool clock = false);
    static void writeTree(const TreeTemplate<Node> & tree,map<string, string> & params,const string & suffix = "",bool verbose = true) throw (Exception);
    static void printOutputTreeHelp();
    static void printParameters(const SubstitutionModel* model, ostream& out);
    static void printParameters(const SubstitutionModelSet* modelSet, ostream& out);
    static void printParameters(const DiscreteDistribution* rDist, ostream& out);
};
