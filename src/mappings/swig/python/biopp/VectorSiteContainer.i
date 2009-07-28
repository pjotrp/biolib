%module bpptest
%{
#include "VectorSiteContainer.h"
using namespace bpp;
%}
%include "Site.i"
%include "SiteContainer.i"
%include "AbstractSequenceContainer.i"
%include "AlignedSequenceContainer.i"
%include "OrderedSequenceContainer.i"
%include "VectorTools.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_iostream.i"
using namespace std;

%rename(__assign__) VectorSiteContainer::operator=;

class VectorSiteContainer:public AbstractSequenceContainer,public virtual SiteContainer
{
  public:
    VectorSiteContainer(const vector<const Site *> & vs, const Alphabet * alpha, bool checkPositions = true) throw (Exception);
    VectorSiteContainer(unsigned int size, const Alphabet * alpha);
    VectorSiteContainer(const vector<string> & names, const Alphabet * alpha);
    VectorSiteContainer(const Alphabet * alpha);
    VectorSiteContainer(const VectorSiteContainer & vsc);
    VectorSiteContainer(const SiteContainer &  sc);
    VectorSiteContainer(const OrderedSequenceContainer & osc);
    VectorSiteContainer(const SequenceContainer &  sc);
    VectorSiteContainer& operator = (const VectorSiteContainer & vsc);
    VectorSiteContainer& operator = (const SiteContainer &  sc);
    VectorSiteContainer& operator = (const OrderedSequenceContainer & osc);
    VectorSiteContainer& operator = (const SequenceContainer &  sc);
    virtual ~VectorSiteContainer();

    VectorSiteContainer * clone() const;
    const Site * getSite(unsigned int siteIndex) const throw (IndexOutOfBoundsException);
    void setSite(unsigned int siteIndex, const Site & site, bool checkPosition = true) throw (Exception);
    Site *    removeSite(unsigned int siteIndex) throw (IndexOutOfBoundsException);
    void deleteSite(unsigned int siteIndex) throw (IndexOutOfBoundsException);
    void addSite(const Site & site, bool checkPosition = true) throw (Exception);
    void addSite(const Site & site, unsigned int siteIndex, bool checkPosition = true) throw (Exception);
    unsigned int getNumberOfSites() const;
    const vector<int> getPositions() const;
    void reindexSites();
    Vint getSitePositions() const;
    void setComments(unsigned int sequenceIndex, const Comments & comments) throw (IndexOutOfBoundsException);
    const Sequence * getSequence(unsigned int sequenceIndex) const throw (IndexOutOfBoundsException);
    const Sequence * getSequence(const string & name ) const throw (SequenceNotFoundException);
    unsigned int getSequencePosition(const string & name) const throw (SequenceNotFoundException);
    Sequence * removeSequence(unsigned int sequenceIndex) throw (IndexOutOfBoundsException);
    Sequence * removeSequence(const string & name ) throw (SequenceNotFoundException);
    void deleteSequence(unsigned int sequenceIndex) throw (IndexOutOfBoundsException);
    void deleteSequence(const string & name ) throw (SequenceNotFoundException);
    unsigned int getNumberOfSequences() const;
    vector<string> getSequencesNames() const;
    void setSequencesNames(const vector<string> & names, bool checkNames = true) throw (Exception);
    void clear();  
    SequenceContainer * createEmptyContainer() const;
    int & valueAt(const string & sequenceName, unsigned int elementIndex) throw (SequenceNotFoundException, IndexOutOfBoundsException);
    const int & valueAt(const string & sequenceName, unsigned int elementIndex) const throw (SequenceNotFoundException, IndexOutOfBoundsException);
    int & operator()(const string & sequenceName, unsigned int elementIndex);
    const int & operator()(const string & sequenceName, unsigned int elementIndex) const;
    int & valueAt(unsigned int sequenceIndex, unsigned int elementIndex) throw (IndexOutOfBoundsException);
    const int & valueAt(unsigned int sequenceIndex, unsigned int elementIndex) const throw (IndexOutOfBoundsException);
    int & operator()(unsigned int sequenceIndex, unsigned int elementIndex);
    const int & operator()(unsigned int sequenceIndex, unsigned int elementIndex) const;
    void addSequence(const Sequence & sequence, bool checkName = true) throw (Exception);
    void addSequence(const Sequence & sequence, unsigned int sequenceIndex, bool checkName = true) throw (Exception);
    void setSequence(const string & name, const Sequence & sequence, bool checkName) throw (Exception);
    void setSequence(unsigned int sequenceIndex, const Sequence & sequence, bool checkName) throw (Exception);
};
