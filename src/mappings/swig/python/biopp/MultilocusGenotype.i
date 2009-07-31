%module bpptest
%{
#include "MultilocusGenotype.h"
using namespace bpp;
%}
%include "std_vector.i"
using namespace std;
%include "Exceptions.i"
%include "MonolocusGenotype.i"
%include "MonolocusGenotypeTools.i"
%include "BiAlleleMonolocusGenotype.i"
%include "MonoAlleleMonolocusGenotype.i"
%include "LocusInfo.i"

class MultilocusGenotype
{
  public: 
    MultilocusGenotype(unsigned int loci_number) throw (BadIntegerException);
    MultilocusGenotype(const MultilocusGenotype & genotype);
    ~MultilocusGenotype();

    void setMonolocusGenotype(unsigned int locus_position, const MonolocusGenotype & monogen) throw (IndexOutOfBoundsException);
    void setMonolocusGenotypeByAlleleKey(unsigned int locus_position, const vector<unsigned int> allele_keys) throw (Exception);
    void setMonolocusGenotypeByAlleleId(unsigned int locus_position, const vector<string> allele_id, const LocusInfo & locus_info) throw (Exception);
    void setMonolocusGenotypeAsMissing(unsigned int locus_position) throw (IndexOutOfBoundsException);
    bool isMonolocusGenotypeMissing(unsigned int locus_position) const throw (IndexOutOfBoundsException);
    const MonolocusGenotype * getMonolocusGenotype(unsigned int locus_position) const throw (IndexOutOfBoundsException);
    unsigned int size() const;
    unsigned int countNonMissingLoci() const;
    unsigned int countHomozygousLoci() const;
    unsigned int countHeterozygousLoci() const;
};
