%module bpptest
%{
#include "SequenceApplicationTools.h"
using namespace bpp;
%}
//#include "alphabets"
//#include "containers"

{
class SequenceApplicationTools
{
  public:
    SequenceApplicationTools();
    virtual ~SequenceApplicationTools();

    static Alphabet * getAlphabet( map<string, string> & params, const string & suffix = "", bool suffixIsOptional = true, bool verbose = true, bool allowGeneric = false);
    static SequenceContainer * getSequenceContainer( const Alphabet * alpha, map<string, string> & params, const string & suffix = "", bool suffixIsOptional = true, bool verbose = true);
    static VectorSiteContainer * getSiteContainer( const Alphabet * alpha, map<string, string> & params, const string & suffix = "", bool suffixIsOptional = true, bool verbose = true);
    static VectorSiteContainer * getSitesToAnalyse( const SiteContainer & allSites, map<string, string> & params, string suffix = "", bool suffixIsOptional = true, bool gapAsUnknown = true, bool verbose = true);
    static void writeSequenceFile( const SequenceContainer & sequences, map<string, string> & params, const string & suffix = "", bool verbose = true);
    static void printInputAlignmentHelp();
    static void printOutputSequenceHelp();
};
} 
