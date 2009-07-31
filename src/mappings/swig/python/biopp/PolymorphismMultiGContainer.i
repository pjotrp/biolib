%module bpptest
%{
#include "PolymorphismMultiGContainer.h"
using namespace bpp;
%}
%include "Clonable.i"
%include "Exceptions.i"
%include "MapTools.i"
%include "TextTools.i"
%include "MultilocusGenotype.i"
%include "GeneralExceptions.i"
//#include <cmath>
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
//#include <set>
//#include <algorithm>
using namespace std;

%rename(__assign__) PolymorphismMultiGContainer::operator=;

class PolymorphismMultiGContainer
{
  public: 
    PolymorphismMultiGContainer();
    PolymorphismMultiGContainer(const PolymorphismMultiGContainer & pmgc);
    ~PolymorphismMultiGContainer();

    PolymorphismMultiGContainer & operator= (const PolymorphismMultiGContainer & pmgc);
    void addMultilocusGenotype(const MultilocusGenotype & mg, unsigned int group);
    const MultilocusGenotype * getMultilocusGenotype(unsigned int position) const throw (IndexOutOfBoundsException);
    MultilocusGenotype * removeMultilocusGenotype(unsigned int position) throw (IndexOutOfBoundsException);
    void deleteMultilocusGenotype(unsigned int position) throw (IndexOutOfBoundsException);
    bool isAligned() const;
    unsigned int getNumberOfLoci() const throw (Exception);
    unsigned int getGroupId(unsigned int position) const throw (IndexOutOfBoundsException);
    void setGroupId(unsigned int position, unsigned int group_id) throw (IndexOutOfBoundsException);
    set<unsigned int> getAllGroupsIds() const;
    vector<string> getAllGroupsNames() const;
    bool groupExists(unsigned int group) const;
    unsigned int getNumberOfGroups() const;
    unsigned int getGroupSize(unsigned int group) const ;
    string getGroupName(unsigned int group_id) const throw (GroupNotFoundException);
    void setGroupName(unsigned int group_id, string name)  throw (GroupNotFoundException);
    void addGroupName(unsigned int group_id, string name)  ;
    unsigned int getLocusGroupSize(unsigned int group, unsigned int locus_position) const;
    unsigned int size() const;
    void clear();
};
