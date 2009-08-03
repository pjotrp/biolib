%module bpp_keyvaltools
%{
#include "KeyvalTools.h"
using namespace bpp;
%}

%include "StringTokenizer.i"
%include "TextTools.i"
%include "Exceptions.i"
//%include "std_map.i"

using namespace std;

class KeyvalException:public Exception
{
  public:
    KeyvalException(const string& message) : Exception(message);
};

%ignore KeyvalTools::KeyvalTools;
%ignore KeyvalTools::~KeyvalTools;

class KeyvalTools
{
  public:
    KeyvalTools();
    virtual ~KeyvalTools();

    static void singleKeyval(const string& desc, string& key, string& val) throw (Exception);
    static void multipleKeyvals(const string& desc, map<string, string>& keyvals) throw (Exception);
    static void parseProcedure(const string& desc, string& name, map<string, string>& args) throw (KeyvalException);
};
