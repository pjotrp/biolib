%module bpptest
%{
#include "SiteExceptions.h"
using namespace bpp;
%}
%include "Exceptions.i"

class Site;
class SiteException:public Exception
{
  public:  
    SiteException(const char *   text, const Site * s = NULL);
    SiteException(const string & text, const Site * s = NULL);
    virtual ~SiteException() throw();

    virtual const Site * getSite() const;
};

class EmptySiteException:public SiteException
{
  public:
    EmptySiteException(const char *   text, const Site * s = NULL);
    EmptySiteException(const string & text, const Site * s = NULL);
    virtual ~EmptySiteException() throw();
};

class SiteWithGapException:public SiteException
{
  public:
    SiteWithGapException(const char *   text, const Site * s = NULL);
    SiteWithGapException(const string & text, const Site * s = NULL);
    virtual ~SiteWithGapException() throw();
};
