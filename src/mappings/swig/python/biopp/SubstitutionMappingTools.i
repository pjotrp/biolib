%module bpptest
%{
#include "SubstitutionMappingTools.h"
using namespace bpp;
%}
%include "ProbabilisticSubstitutionMapping.i"
%include "SubstitutionCount.i"
%include "DRTreeLikelihood.i"

%ignore SubstitutionMappingTools::SubstitutionMappingTools;
%ignore SubstitutionMappingTools::~SubstitutionMappingTools;

class SubstitutionMappingTools
{
  public:
    SubstitutionMappingTools();
    virtual ~SubstitutionMappingTools();

    static ProbabilisticSubstitutionMapping * computeSubstitutionVectors(const DRTreeLikelihood & drtl,SubstitutionCount & substitutionCount,bool verbose = true) throw (Exception);
    static ProbabilisticSubstitutionMapping * computeSubstitutionVectorsNoAveraging(const DRTreeLikelihood & drtl,SubstitutionCount & substitutionCount,bool verbose = true) throw (Exception);
    static ProbabilisticSubstitutionMapping * computeSubstitutionVectorsNoAveragingMarginal(const DRTreeLikelihood & drtl,SubstitutionCount & substitutionCount,bool verbose = true) throw (Exception);
    static ProbabilisticSubstitutionMapping * computeSubstitutionVectorsMarginal(const DRTreeLikelihood & drtl,SubstitutionCount & substitutionCount,bool verbose = true) throw (Exception);
    static void writeToStream(const ProbabilisticSubstitutionMapping & substitutions,const SiteContainer & sites,ostream & out) throw (IOException);
    static void readFromStream(istream & in, ProbabilisticSubstitutionMapping & substitutions) throw (IOException);
};
