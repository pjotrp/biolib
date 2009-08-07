%module bpp_atttools
%{
#include "AttributesTools.h"
using namespace bpp;
%}

// From the STL:
using namespace std;

%ignore AttributesTools::AttributesTools;
%ignore AttributesTools::~AttributesTools;

class AttributesTools
{
  
  public:
    AttributesTools();
    virtual ~AttributesTools();

    %ignore getVector(int argc, char * argv[]);

    static vector<string> getVector(int argc, char * argv[]);
    static map<string, string> getAttributesMap(const vector<string> & argv, const string & delimiter = "=");
    static void getAttributesMap(const vector<string> & argv, map<string, string> & am, const string & delimiter = "=");
    static map<string, string> getAttributesMapFromFile(const string & file, const string & delimiter);
    static void getAttributesMapFromFile( const string & file, map<string, string> & params, const string & delimiter);
    static void actualizeAttributesMap( map<string, string> & attMap, const map<string, string> & atts);
    static void resolveVariables(map<string, string> & am, char varCode = '$', char varBeg = '(', char varEnd = ')');
    static map<string, string> parseOptions(int args, char ** argv);

    %extend {
      static vector<string> getVector(int argc, char **argv) { return AttributesTools::getVector(argc, argv);}
    }
};
