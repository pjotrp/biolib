%module bpptest
%{
#include "LocusInfo.h"
using namespace bpp;
%}
%include "std_vector.i"
using namespace std;
%include "AlleleInfo.i"
%include "GeneralExceptions.i"
%include "Exceptions.i"

class LocusInfo
{
  public:
    static unsigned int HAPLODIPLOID;
    static unsigned int HAPLOID;
    static unsigned int DIPLOID;
    static unsigned int UNKNOWN;

    LocusInfo(const string &name, const unsigned int ploidy = DIPLOID);
    LocusInfo(const LocusInfo & locus_info);
    virtual ~LocusInfo();

    string getName() const;
    unsigned int getPloidy() const;
    void addAlleleInfo(const AlleleInfo &allele) throw (BadIdentifierException);
    AlleleInfo * getAlleleInfoById(const string & id) const throw (AlleleNotFoundException);
    AlleleInfo * getAlleleInfoByKey(unsigned int key) const throw (IndexOutOfBoundsException);
    unsigned int getAlleleInfoKey(const string & id) const throw (AlleleNotFoundException);
    unsigned int getNumberOfAlleles() const;
    void clear();
};
