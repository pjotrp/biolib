%module bpptest
%{
#include "SiteContainerExceptions.h"
using namespace bpp;
%}
%include "Exceptions.i"

class SiteNotFoundException:public Exception
{
  public:  
    SiteNotFoundException(const char *   text, const char * sId = "");
    SiteNotFoundException(const string & text, const string & sId = "");
    ~SiteNotFoundException() throw();

    virtual const string getSiteId() const;
};
