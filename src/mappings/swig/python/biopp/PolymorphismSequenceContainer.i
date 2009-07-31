%module bpptest
%{
#include "PolymorphismSequenceContainer.h"
using namespace bpp;
%}
#include <set>
using namespace std;
%include "Clonable.i"
%include "StringTokenizer.i"
%include "TextTools.i"
%include "VectorSiteContainer.i"
%include "SequenceContainerTools.i"

class PolymorphismSequenceContainer:public VectorSiteContainer
{
  public: 
    PolymorphismSequenceContainer(const Alphabet *alpha);
    PolymorphismSequenceContainer(unsigned int size, const Alphabet *alpha);
    PolymorphismSequenceContainer(const OrderedSequenceContainer & sc);
    PolymorphismSequenceContainer(const SiteContainer & sc);
    PolymorphismSequenceContainer(const PolymorphismSequenceContainer & psc);
    PolymorphismSequenceContainer & operator= (const PolymorphismSequenceContainer & psc);
    virtual ~PolymorphismSequenceContainer();
    PolymorphismSequenceContainer * clone() const;

    Sequence * removeSequence(unsigned int index) throw (IndexOutOfBoundsException);
    Sequence * removeSequence(const string &name) throw (SequenceNotFoundException);
    void deleteSequence(unsigned int index) throw (IndexOutOfBoundsException);
    void deleteSequence(const string &name) throw (SequenceNotFoundException);
    void addSequence(const Sequence &sequence,unsigned int effectif=1,  bool checkNames=true) throw (Exception);
    void clear();
    unsigned int getGroupId(unsigned int index) const throw (IndexOutOfBoundsException);
    unsigned int getGroupId(const string & name) const throw (SequenceNotFoundException);
    set<unsigned int> getAllGroupsIds() const;
    void setGroupId(unsigned int index, unsigned int group_id) throw (IndexOutOfBoundsException);
    void setGroupId(const string & name, unsigned int group_id) throw (SequenceNotFoundException);
    unsigned int getNumberOfGroups() const;
    bool isIngroupMember(unsigned int index) const throw (IndexOutOfBoundsException);
    bool isIngroupMember(const string &name) const throw (SequenceNotFoundException);
    void setAsIngroupMember(unsigned int index) throw (IndexOutOfBoundsException);
    void setAsIngroupMember(const string &name) throw (SequenceNotFoundException);
    void setAsOutgroupMember(unsigned int index) throw (IndexOutOfBoundsException);
    void setAsOutgroupMember(const string &name) throw (SequenceNotFoundException);
    void setSequenceCount(unsigned int index, unsigned int count) throw (Exception);
    void setSequenceCount(const string &name, unsigned int count) throw (Exception);
    void incrementSequenceCount(unsigned int index) throw (IndexOutOfBoundsException);
    void incrementSequenceCount(const string &name) throw (SequenceNotFoundException);
    void decrementSequenceCount(unsigned int index) throw (Exception);
    void decrementSequenceCount(const string & name) throw (Exception);
    unsigned int getSequenceCount(unsigned int index) const throw (IndexOutOfBoundsException);
    unsigned int getSequenceCount(const string &name) const throw (SequenceNotFoundException);
};
