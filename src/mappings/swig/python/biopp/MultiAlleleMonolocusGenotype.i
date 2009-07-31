%module bpptest
%{
#include "MultiAlleleMonolocusGenotype.h"
using namespace bpp;
%}
%include "std_vector.i"
using namespace std;
%include "Exceptions.i"
%include "MonolocusGenotype.i"

%rename(__assign__) MultiAlleleMonolocusGenotype::operator=;
%rename(__eq__) MultiAlleleMonolocusGenotype::operator==;

class MultiAlleleMonolocusGenotype:public MonolocusGenotype
{
  public: 
    MultiAlleleMonolocusGenotype(vector<unsigned int> allele_index);
    MultiAlleleMonolocusGenotype(const MultiAlleleMonolocusGenotype & mmg);
    ~MultiAlleleMonolocusGenotype();

    MultiAlleleMonolocusGenotype & operator= (const MultiAlleleMonolocusGenotype & mmg);
    bool operator== (const MultiAlleleMonolocusGenotype & mmg) const;
    bool isHomozygous() const;
    vector<unsigned int> getAlleleIndex() const;
    Clonable * clone() const;
};
