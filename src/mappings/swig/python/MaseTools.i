%module bpptest
%{
#include "MaseTools.h"
using namespace bpp;
%}
%include "SequenceContainer.i"
%include "OrderedSequenceContainer.i"
%include "SequenceContainerTools.i"
%include "SiteContainer.i"
%include "SiteContainerTools.i"
%include "Exceptions.i"
using namespace std;

class MaseTools
{
  public:
    static SiteSelection getSiteSet(const Comments & maseFileHeader, const string & setName) throw (IOException);
    static SequenceSelection getSequenceSet(const Comments & maseFileHeader, const string & setName) throw (IOException);
    static SiteContainer * getSelectedSites(const SiteContainer & sequences, const string & setName) throw (IOException);
    static SequenceContainer * getSelectedSequences(const OrderedSequenceContainer & sequences, const string & setName) throw (IOException);
    static map<string, unsigned int> getAvailableSiteSelections(const Comments & maseHeader);
    static map<string, unsigned int> getAvailableSequenceSelections(const Comments & maseHeader);
    static unsigned int getPhase(const Comments & maseFileHeader, const string &setName) throw (Exception);
};
