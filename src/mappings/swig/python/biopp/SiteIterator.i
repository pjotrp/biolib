%module bpptest
%{
#include "SiteIterator.h"
using namespace bpp;
%}
%include "Site.i"
%include "SiteContainer.i"

class SiteIterator
{
  public:
    SiteIterator();
    virtual ~SiteIterator();

    virtual const Site * nextSite() = 0;
    virtual bool hasMoreSites() const = 0;
};

class AbstractSiteIterator: public SiteIterator
{
  public:
    AbstractSiteIterator(const SiteContainer & sites);
    virtual ~AbstractSiteIterator();

    virtual const Site * nextSite() = 0;
    virtual bool hasMoreSites() const = 0;
};

class SimpleSiteIterator: public AbstractSiteIterator
{
  public:
    SimpleSiteIterator(const SiteContainer & sites);
    virtual ~SimpleSiteIterator();

    const Site * nextSite();
    bool hasMoreSites() const;
};

class NoGapSiteIterator: public AbstractSiteIterator
{
  public:
    NoGapSiteIterator(const SiteContainer & sites);
    virtual ~NoGapSiteIterator();

    const Site * nextSite();
    bool hasMoreSites() const;
    int nextSiteWithoutGapPosition(int current) const;
    int previousSiteWithoutGapPosition(int current) const;
};
class CompleteSiteIterator: public AbstractSiteIterator
{
  public:
    CompleteSiteIterator(const SiteContainer & sites);
    virtual ~CompleteSiteIterator();

    const Site * nextSite();
    bool hasMoreSites() const;
    int nextCompleteSitePosition(int current) const;
    int previousCompleteSitePosition(int current) const;
};
