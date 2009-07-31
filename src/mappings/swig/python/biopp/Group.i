%module bpptest
%{
#include "Group.h"
using namespace bpp;
%}
%include "std_vector.i"
using namespace std;
%include "Exceptions.i"
%include "VectorSequenceContainer.i"
%include "VectorSiteContainer.i"
%include "SequenceContainerTools.i"
%include "Individual.i"
%include "GeneralExceptions.i"

class Group
{
  public: 
    Group(unsigned int group_id);
    Group(const Group & group);
    Group(const Group & group, unsigned int group_id);
    ~Group();

    Group & operator= (const Group & group);
    void setGroupId(unsigned int group_id);
    string getGroupName() const;
    void setGroupName(string group_name);
    unsigned int getGroupId() const;
    void addIndividual(const Individual & ind) throw (BadIdentifierException);
    void addEmptyIndividual(const string & individual_id) throw (BadIdentifierException);
    unsigned int getNumberOfIndividuals() const;
    unsigned int getMaxNumberOfSequences() const;
    unsigned int getIndividualPosition(const string individual_id) const throw (IndividualNotFoundException);
    const Individual * getIndividualById(const string individual_id) const;
    const Individual * getIndividualAtPosition(unsigned int individual_position) const throw (IndexOutOfBoundsException);
    Individual * removeIndividualById(const string individual_id) throw (IndividualNotFoundException);
    Individual * removeIndividualAtPosition(unsigned int individual_position) throw (IndexOutOfBoundsException);
    void deleteIndividualById(const string individual_id) throw (IndividualNotFoundException);
    void deleteIndividualAtPosition(unsigned int individual_position) throw (IndexOutOfBoundsException);
    void clear();
    void setIndividualSexAtPosition(unsigned int individual_position, const unsigned short sex) throw (IndexOutOfBoundsException);
    unsigned short getIndividualSexAtPosition(unsigned int individual_position) const throw (IndexOutOfBoundsException);
    void setIndividualDateAtPosition(unsigned int individual_position, const Date & date) throw (IndexOutOfBoundsException);
    const Date * getIndividualDateAtPosition(unsigned int individual_position) const throw (Exception);
    void setIndividualCoordAtPosition(unsigned int individual_position, const Coord<double> & coord) throw (IndexOutOfBoundsException);
    const Coord<double> * getIndividualCoordAtPosition(unsigned int individual_position) const throw (Exception);
    void setIndividualLocalityAtPosition(unsigned int individual_position, const Locality<double> * locality) throw (IndexOutOfBoundsException);
    const Locality<double> * getIndividualLocalityAtPosition(unsigned int individual_position) const throw (Exception);
    void addIndividualSequenceAtPosition(unsigned int individual_position, unsigned int sequence_position, const Sequence & sequence) throw (Exception);
    const Sequence * getIndividualSequenceByName(unsigned int individual_position, const string & sequence_name) const throw (Exception);
    const Sequence * getIndividualSequenceAtPosition(unsigned int individual_position, unsigned int sequence_position) const throw (Exception);
    void deleteIndividualSequenceByName(unsigned int individual_position, const string & sequence_name) throw (Exception);
    void deleteIndividualSequenceAtPosition(unsigned int individual_position, unsigned int sequence_position) throw (Exception);
    bool hasIndividualSequences(unsigned int individual_position) const throw (IndexOutOfBoundsException);
    vector<string> getIndividualSequencesNames(unsigned int individual_position) const throw (Exception);
    unsigned int getIndividualSequencePosition(unsigned int individual_position, const string & sequence_name) const throw (Exception);
    unsigned int getIndividualNumberOfSequences(unsigned int individual_position) const throw (Exception);
    void setIndividualSequences(unsigned int individual_position, const MapSequenceContainer & msc) throw (IndexOutOfBoundsException);
    void setIndividualGenotype(unsigned int individual_position, const MultilocusGenotype & genotype) throw (IndexOutOfBoundsException);
    void initIndividualGenotype(unsigned int individual_position, unsigned int loci_number) throw (Exception);
    void deleteIndividualGenotype(unsigned int individual_position) throw (IndexOutOfBoundsException);
    bool hasIndividualGenotype(unsigned int individual_position) const throw (IndexOutOfBoundsException);
    void setIndividualMonolocusGenotype(unsigned int individual_position, unsigned int locus_position, const MonolocusGenotype & monogen) throw (Exception);
    void setIndividualMonolocusGenotypeByAlleleKey(unsigned int individual_position, unsigned int locus_position, const vector<unsigned int> allele_keys) throw (Exception);
    void setIndividualMonolocusGenotypeByAlleleId(unsigned int individual_position, unsigned int locus_position, const vector<string> allele_id, const LocusInfo & locus_info) throw (Exception);
    const MonolocusGenotype * getIndividualMonolocusGenotype(unsigned int individual_position, unsigned int locus_position) const throw (Exception);
    bool hasSequenceData() const;
    const Alphabet * getAlphabet() const throw (NullPointerException);
    unsigned int getGroupSizeForLocus(unsigned int locus_position) const;
    unsigned int getGroupSizeForSequence(unsigned int sequence_position) const;
};
