%module bpptest
%{
#include "SiteContainer.h"
using namespace bpp;
%}

%include "Site.i"
%include "OrderedSequenceContainer.i"
%include "SequenceContainerExceptions.i"
%include "Exceptions.i"
%include "VectorTools.i"
//#include <cstdlib>

using namespace std;

class SiteContainer:public virtual OrderedSequenceContainer
{
  public:
    SiteContainer();
    virtual ~SiteContainer();
    SiteContainer * clone() const = 0;
    
    virtual const Site * getSite(unsigned int siteIndex) const throw (IndexOutOfBoundsException) = 0;
    virtual void setSite(unsigned int siteIndex, const Site & site, bool checkPosition) throw (Exception) = 0;
    virtual Site * removeSite(unsigned int siteIndex) throw (IndexOutOfBoundsException) = 0;
    virtual void deleteSite(unsigned int siteIndex) throw (IndexOutOfBoundsException) = 0;
    virtual unsigned int getNumberOfSites() const = 0;
    virtual void reindexSites() = 0;
    virtual Vint getSitePositions() const = 0;
};
