%module bpptest
%{
#include "DataSet.h"
using namespace bpp;
%}
//#include <algorithm>
%include "std_vector.i"
%include "std_map.i"
using namespace std;
%include "Exceptions.i"
%include "MapTools.i"
%include "Group.i"
%include "Individual.i"
%include "Locality.i"
%include "GeneralExceptions.i"
%include "AnalyzedLoci.i"
%include "AnalyzedSequences.i"
%include "PolymorphismMultiGContainer.i"
%include "PolymorphismSequenceContainer.i"

class DataSet
{
  public: 
    DataSet();
    ~DataSet();

    void addLocality(Locality<double> & locality) throw (BadIdentifierException);
    unsigned int getLocalityPosition(const string & name) const throw (LocalityNotFoundException);
    const Locality<double> * getLocalityAtPosition(unsigned int locality_position) const throw (IndexOutOfBoundsException);
    const Locality<double> * getLocalityByName(const string & name) const throw (LocalityNotFoundException);
    void deleteLocalityAtPosition(unsigned int locality_position) throw (IndexOutOfBoundsException);
    void deleteLocalityByName(const string & name) throw (LocalityNotFoundException);
    unsigned int getNumberOfLocalities() const;
    bool hasLocality() const;
    void addGroup(const Group & group) throw (BadIdentifierException);
    void addEmptyGroup(unsigned int group_id) throw (BadIdentifierException);
    const Group * getGroupById(unsigned int group_id) const;
    unsigned int getGroupPosition(unsigned int group_id) const throw (GroupNotFoundException);
    string getGroupName(unsigned int group_id) const throw (GroupNotFoundException);
    void setGroupName(unsigned int group_id, string group_name) const throw (GroupNotFoundException);
    const Group * getGroupAtPosition(unsigned int group_position) const throw (IndexOutOfBoundsException);
    void deleteGroupAtPosition(unsigned int group_position) throw (IndexOutOfBoundsException);
    unsigned int getNumberOfGroups() const;
    void mergeTwoGroups(unsigned int source_id, unsigned int target_id) throw (GroupNotFoundException);
    void mergeGroups(vector<unsigned int> & group_ids) throw (GroupNotFoundException);
    void splitGroup(unsigned int group_id, vector<unsigned int> individuals_selection) throw (Exception);
    void addIndividualToGroup(unsigned int group_position, const Individual & individual) throw (Exception);
    void addEmptyIndividualToGroup(unsigned int group_position, const string & individual_id) throw (Exception);
    unsigned int getNumberOfIndividualsInGroup(unsigned int group_position) const throw (IndexOutOfBoundsException);
    unsigned int getIndividualPositionInGroup(unsigned int group_position, const string & individual_id) const throw (Exception);
    const Individual * getIndividualAtPositionFromGroup(unsigned int group_position, unsigned int individual_position) const throw (IndexOutOfBoundsException);
    const Individual * getIndividualByIdFromGroup(unsigned int group_position, const string & individual_id) const throw (Exception);
    void deleteIndividualAtPositionFromGroup(unsigned int group_position, unsigned int individual_position) throw (IndexOutOfBoundsException);
    void deleteIndividualByIdFromGroup(unsigned int group_position, const string & individual_id) throw (Exception);
    void setIndividualSexInGroup(unsigned int group_position, unsigned int individual_position, const unsigned short sex) throw (IndexOutOfBoundsException);
    unsigned short getIndividualSexInGroup(unsigned int group_position, unsigned int individual_position) const throw (IndexOutOfBoundsException);
    void setIndividualDateInGroup(unsigned int group_position, unsigned int individual_position, const Date & date) throw (IndexOutOfBoundsException);
    const Date * getIndividualDateInGroup(unsigned int group_position, unsigned int individual_position) const throw (Exception);
    void setIndividualCoordInGroup(unsigned int group_position, unsigned int individual_position, const Coord<double> & coord) throw (IndexOutOfBoundsException);
    const Coord<double> * getIndividualCoordInGroup(unsigned int group_position, unsigned int individual_position) const throw (Exception);
    void setIndividualLocalityInGroupByName(unsigned int group_position, unsigned int individual_position, const string & locality_name) throw (Exception);
    const Locality<double> * getIndividualLocalityInGroup(unsigned int group_position, unsigned int individual_position) const throw (Exception);
    void addIndividualSequenceInGroup(unsigned int group_position, unsigned int individual_position, unsigned int sequence_position, const Sequence & sequence) throw (Exception);
    const Sequence * getIndividualSequenceByNameInGroup(unsigned int group_position, unsigned int individual_position, const string & sequence_name) const throw (Exception);
    const Sequence * getIndividualSequenceAtPositionInGroup(unsigned int group_position, unsigned int individual_position, unsigned int sequence_position) const throw (Exception);
    void deleteIndividualSequenceByNameInGroup(unsigned int group_position, unsigned int individual_position, const string & sequence_name) throw (Exception);
    void deleteIndividualSequenceAtPositionInGroup(unsigned int group_position, unsigned int individual_position, unsigned int sequence_position) throw (Exception);
    vector<string> getIndividualSequencesNamesInGroup(unsigned int group_position, unsigned int individual_position) const throw (Exception);
    unsigned int getIndividualSequencePositionInGroup(unsigned int group_position, unsigned int individual_position, const string & sequence_name) const throw (Exception);
    unsigned int getIndividualNumberOfSequencesInGroup(unsigned int group_position, unsigned int individual_position) const throw (Exception);
    void setIndividualGenotypeInGroup(unsigned int group_position, unsigned int individual_position, const MultilocusGenotype & genotype) throw (Exception);
    void initIndividualGenotypeInGroup(unsigned int group_position, unsigned int individual_position) throw (Exception);
    void deleteIndividualGenotypeInGroup(unsigned int group_position, unsigned int individual_position) throw (IndexOutOfBoundsException);
    void setIndividualMonolocusGenotypeInGroup(unsigned int group_position, unsigned int individual_position, unsigned int locus_position, const MonolocusGenotype & monogen) throw (Exception);
    void setIndividualMonolocusGenotypeByAlleleKeyInGroup(unsigned int group_position, unsigned int individual_position, unsigned int locus_position, const vector<unsigned int> allele_keys) throw (Exception);
    void setIndividualMonolocusGenotypeByAlleleIdInGroup(unsigned int group_position, unsigned int individual_position, unsigned int locus_position, const vector<string> allele_id) throw (Exception);
    const MonolocusGenotype * getIndividualMonolocusGenotypeInGroup(unsigned int group_position, unsigned int individual_position, unsigned int locus_position) const throw (Exception);
    void setAlphabet(const Alphabet * alpha);
    void setAlphabet(const string & alpha_type);
    const Alphabet * getAlphabet() const throw (NullPointerException);
    string getAlphabetType() const throw (NullPointerException);
    void setAnalyzedLoci(const AnalyzedLoci & analyzedLoci) throw (Exception);
    void initAnalyzedLoci(unsigned int number_of_loci) throw (Exception);
    const AnalyzedLoci * getAnalyzedLoci() const throw (NullPointerException);
    void deleteAnalyzedLoci();
    void setLocusInfo(unsigned int locus_position, const LocusInfo & locus) throw (Exception);
    const LocusInfo * getLocusInfoByName(const string & locus_name) const throw (Exception);
    const LocusInfo * getLocusInfoAtPosition(unsigned int locus_position) const throw (Exception);
    void addAlleleInfoByLocusName(const string & locus_name, const AlleleInfo & allele) throw (Exception);
    void addAlleleInfoByLocusPosition(unsigned int locus_position, const AlleleInfo & allele) throw (Exception);
    unsigned int getNumberOfLoci() const throw (NullPointerException);
    unsigned int getPloidyByLocusName(const string & locus_name) const throw (Exception);
    unsigned int getPloidyByLocusPosition(unsigned int locus_position) const throw (Exception);
    PolymorphismMultiGContainer * getPolymorphismMultiGContainer() const;
    PolymorphismMultiGContainer * getPolymorphismMultiGContainer(const map<unsigned int, vector<unsigned int> > & selection) const throw (Exception);
    PolymorphismSequenceContainer * getPolymorphismSequenceContainer(const map<unsigned int, vector<unsigned int> > & selection, unsigned int sequence_position) const throw (Exception);
    bool hasSequenceData() const;
    bool hasAlleleicData() const;
};
