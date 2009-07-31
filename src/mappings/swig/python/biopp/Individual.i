%module bpptest
%{
#include "Individual.h"
using namespace bpp;
%}
%include "std_map.i"
%include "std_vector.i"
using namespace std;
%include "Clonable.i"
%include "Exceptions.i"
%include "TextTools.i"
%include "Sequence.i"
%include "OrderedSequenceContainer.i"
%include "MapSequenceContainer.i"
%include "SequenceExceptions.i"
%include "Locality.i"
%include "Coord.i"
%include "Date.i"
%include "MultilocusGenotype.i"
%include "GeneralExceptions.i"

%rename(__assign__) Individual::operator=;

class Individual
{
  public: 
    Individual();
    Individual(const string & id);
    Individual(const string & id, const Date & date, const Coord<double> & coord, Locality<double> * locality, const unsigned short sex);
    Individual(const Individual &ind);
    virtual ~Individual();

    Individual & operator= (const Individual & ind);
    void setId(const string id);
    string getId() const;
    void setSex(const unsigned short sex);
    unsigned short getSex() const;
    void setDate(const Date & date);
    const Date * getDate() const throw (NullPointerException);
    bool hasDate() const;
    void setCoord(const Coord<double> & coord);
    void setCoord(const double x, const double y);
    const Coord<double> * getCoord() const throw(NullPointerException);
    bool hasCoord() const;
    void setX(const double x) throw(NullPointerException);
    void setY(const double y) throw(NullPointerException);
    double getX() const throw(NullPointerException);
    double getY() const throw(NullPointerException);
    void setLocality(const Locality<double> * locality);
    const Locality<double> * getLocality() const throw (NullPointerException);
    bool hasLocality() const;
    void addSequence(unsigned int sequence_key, const Sequence & sequence) throw (Exception);
    const Sequence * getSequenceByName(const string & sequence_name) const throw(Exception);
    const Sequence * getSequenceAtPosition(const unsigned int sequence_position) const throw(Exception);
    void deleteSequenceByName(const string & sequence_name) throw (Exception);
    void deleteSequenceAtPosition(unsigned int sequence_position) throw (Exception);
    bool hasSequences() const;
    bool hasSequenceAtPosition(unsigned int position) const;
    const Alphabet * getSequenceAlphabet() const throw (NullPointerException);
    vector<string> getSequencesNames() const throw (NullPointerException);
    vector<unsigned int> getSequencesPositions() const throw (NullPointerException);
    unsigned int getSequencePosition(const string & sequence_name) const throw (Exception);
    unsigned int getNumberOfSequences() const;
    void setSequences(const MapSequenceContainer & msc);
    const OrderedSequenceContainer * getSequences() const throw (NullPointerException);
    void setGenotype(const MultilocusGenotype & genotype);
    void initGenotype(unsigned int loci_number) throw (Exception);
    const MultilocusGenotype * getGenotype() const throw (NullPointerException);
    void deleteGenotype();
    bool hasGenotype() const;
    void setMonolocusGenotype(unsigned int locus_position, const MonolocusGenotype & monogen) throw (Exception);
    void setMonolocusGenotypeByAlleleKey(unsigned int locus_position, const vector<unsigned int> allele_keys) throw (Exception);
    void setMonolocusGenotypeByAlleleId(unsigned int locus_position, const vector<string> allele_id, const LocusInfo & locus_info) throw (Exception);
    const MonolocusGenotype * getMonolocusGenotype(unsigned int locus_position) throw (Exception);
    unsigned int countNonMissingLoci() const throw (NullPointerException);
    unsigned int countHomozygousLoci() const throw (NullPointerException);
    unsigned int countHeterozygousLoci() const throw (NullPointerException);
};
