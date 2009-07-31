%module bpptest
%{
#include "BiAlleleMonolocusGenotype.h"
using namespace bpp;
%}
%include "std_vector.i"
using namespace std;
%include "Exceptions.i"
%include "MonolocusGenotype.i"

%rename(__assign__) BiAlleleMonolocusGenotype::operator=;
%rename(__eq__) BiAlleleMonolocusGenotype::operator==;

class BiAlleleMonolocusGenotype:public MonolocusGenotype
{
  public: 
    BiAlleleMonolocusGenotype(unsigned int first_allele_index, unsigned int second_allele_index);
    BiAlleleMonolocusGenotype(vector<unsigned int> allele_index) throw (BadIntegerException);
    BiAlleleMonolocusGenotype(const BiAlleleMonolocusGenotype & bmg);
    ~BiAlleleMonolocusGenotype();

    BiAlleleMonolocusGenotype & operator= (const BiAlleleMonolocusGenotype & bmg);
    bool operator== (const BiAlleleMonolocusGenotype & bmg) const;
    unsigned int getFirstAlleleIndex() const;
    unsigned int getSecondAlleleIndex() const;
    bool isHomozygous() const;
    vector<unsigned int> getAlleleIndex() const;
    Clonable * clone() const;
};
