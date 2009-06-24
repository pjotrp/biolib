%module bpp_keyvaltools
%{
#include "StringTokenizer.h"
#include "TextTools.h"
#include "Exceptions.h"
#include <map>
%}

%include "StringTokenizer.i"
%include "TextTools.i"
%include "Exceptions.i"
%include "std_map.i"

using namespace std;

namespace bpp
{

class KeyvalException :
  public Exception
{
  public:
    KeyvalException(const string& message) : Exception(message) {}
};


class KeyvalTools
{
  public:
    KeyvalTools();
    virtual ~KeyvalTools();

  public:
    static void singleKeyval(const string& desc, string& key, string& val) throw (Exception);
    static void multipleKeyvals(const string& desc, map<string, string>& keyvals) throw (Exception);
    static void parseProcedure(const string& desc, string& name, map<string, string>& args) throw (KeyvalException);
};

} //End of namespace bpp.
