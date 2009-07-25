%module bpptest
%{
#include "AlignedSequenceContainer.h"
using namespace bpp;
%}
%include "Site.i"
%include "SiteContainer.i"
%include "OrderedSequenceContainer.i"
%include "VectorSequenceContainer.i"
%include "Exceptions.i"
%include "std_string.i"
using namespace std;

class AlignedSequenceContainer:public virtual VectorSequenceContainer,public virtual SiteContainer
{
  public:
    AlignedSequenceContainer(const Alphabet * alpha);
    AlignedSequenceContainer(const AlignedSequenceContainer & asc);
    AlignedSequenceContainer(const SiteContainer &  sc);
    AlignedSequenceContainer(const OrderedSequenceContainer & osc) throw (SequenceNotAlignedException);
    AlignedSequenceContainer & operator = (const AlignedSequenceContainer & asc);
    AlignedSequenceContainer & operator = (const            SiteContainer &  sc);
    AlignedSequenceContainer & operator = (const OrderedSequenceContainer & osc) throw (SequenceNotAlignedException);
    virtual ~AlignedSequenceContainer();

    AlignedSequenceContainer * clone() const;
    const Site * getSite(unsigned int siteIndex) const throw (IndexOutOfBoundsException) ;
    void         setSite(unsigned int siteIndex, const Site & site, bool checkPosition = true) throw (Exception) ;
    Site *    removeSite(unsigned int siteIndex) throw (IndexOutOfBoundsException) ;
    void      deleteSite(unsigned int siteIndex) throw (IndexOutOfBoundsException) ;
    void addSite(const Site & site, bool checkPosition = true) throw (Exception);
    void addSite(const Site & site, unsigned int siteIndex, bool checkPosition = true) throw (Exception);
    unsigned int getNumberOfSites() const;
    Vint getSitePositions() const;
    void reindexSites();
    void clear();
    SequenceContainer * createEmptyContainer() const;
    void setSequence(const string & name, const Sequence & sequence, bool checkName = true) throw (Exception);
    void setSequence(unsigned int sequenceIndex, const Sequence & sequence, bool checkName = true) throw (Exception);
    void addSequence(const Sequence & sequence, bool checkName = true) throw (Exception);
    void addSequence(const Sequence & sequence, unsigned int sequenceIndex, bool checkName = true) throw (Exception);
};
