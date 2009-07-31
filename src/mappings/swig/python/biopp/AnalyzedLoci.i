%module bpptest
%{
#include "AnalyzedLoci.h"
using namespace bpp;
%}
%include "std_vector.i"
using namespace std;
%include "Exceptions.i"
%include "LocusInfo.i"
%include "GeneralExceptions.i"

class AnalyzedLoci
{
  public: 
    AnalyzedLoci(unsigned int number_of_loci);
    AnalyzedLoci(const AnalyzedLoci & analyzed_loci);
    ~AnalyzedLoci();

    void setLocusInfo(unsigned int locus_position, const LocusInfo & locus) throw (IndexOutOfBoundsException);
    unsigned int getLocusInfoPosition(const string & locus_name) const throw (BadIdentifierException);
    const LocusInfo * getLocusInfoByName(const string & locus_name) const throw (BadIdentifierException);
    const LocusInfo * getLocusInfoAtPosition(unsigned int locus_position) const throw (Exception);
    void addAlleleInfoByLocusName(const string & locus_name, const AlleleInfo & allele) throw (Exception);
    void addAlleleInfoByLocusPosition(unsigned int locus_position, const AlleleInfo & allele) throw (Exception);
    unsigned int getNumberOfLoci() const;
    vector<unsigned int> getNumberOfAlleles() const;
    unsigned int getPloidyByLocusName(const string & locus_name) const throw (LocusNotFoundException);
    unsigned int getPloidyByLocusPosition(unsigned int locus_position) const throw (IndexOutOfBoundsException);
};
