%module bpptest
%{
#include "MonoAlleleMonolocusGenotype.h"
using namespace bpp;
%}
%include "Exceptions.i"
%include "MonolocusGenotype.i"

%rename(__assign__) MonoAlleleMonolocusGenotype::operator=;
%rename(__eq__) MonoAlleleMonolocusGenotype::operator==;

class MonoAlleleMonolocusGenotype:public MonolocusGenotype
{
  public: 
    MonoAlleleMonolocusGenotype(unsigned int allele_index);
    MonoAlleleMonolocusGenotype(vector<unsigned int> allele_index) throw (BadIntegerException);
    MonoAlleleMonolocusGenotype(const MonoAlleleMonolocusGenotype & mmg);
    ~MonoAlleleMonolocusGenotype();

    MonoAlleleMonolocusGenotype & operator= (const MonoAlleleMonolocusGenotype & mmg);
    virtual bool operator== (const MonoAlleleMonolocusGenotype & mmg) const;
    vector<unsigned int> getAlleleIndex() const;
    Clonable * clone() const;
};
