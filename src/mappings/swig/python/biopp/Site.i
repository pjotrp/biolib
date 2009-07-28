%module bpptest
%{
#include "Site.h"
using namespace bpp;
%}

%include "SymbolList.i"
%include "SiteExceptions.i"

using namespace std;

%rename(__assign__) Site::operator=;
%rename(__eq__) operator==;
%rename(__lt__) operator<;

class Site:public SymbolList 
{  
  public:
    Site(const Alphabet * alpha);
    Site(const Alphabet * alpha, int position);
    Site(const vector<string> & site, const Alphabet * alpha) throw (BadCharException);
    Site(const vector<string> & site, const Alphabet * alpha, int position) throw (BadCharException);
    Site(const vector<int> & site, const Alphabet * alpha) throw (BadIntException);
    Site(const vector<int> & site, const Alphabet * alpha, int position) throw (BadIntException);
    Site(const Site & site);
    Site operator = (const Site & s);
    virtual ~Site();
    
    Site* clone() const;
    virtual int getPosition() const;
    virtual void setPosition(int position);
};

bool operator == (const Site & site1, const Site & site2);
bool operator < (const Site & site1, const Site & site2);
