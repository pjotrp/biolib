%module bpptest
%{
#include "MonolocusGenotypeTools.h"
using namespace bpp;
%}
%include "std_vector.i"
using namespace std;
%include "Exceptions.i"
%include "MonolocusGenotype.i"

%ignore MonolocusGenotypeTools::MonolocusGenotypeTools;
%ignore MonolocusGenotypeTools::~MonolocusGenotypeTools;

class MonolocusGenotypeTools
{
  public:
  static MonolocusGenotype * buildMonolocusGenotypeByAlleleKey(const vector<unsigned int> allele_keys) throw (Exception);
};
