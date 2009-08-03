%module bpp_filetools
%{
#include "FileTools.h"
using namespace bpp;
%}

%include "std_string.i"
%include "std_vector.i"
//%include "std_iostream.i"

using namespace std;

%ignore FileTools::FileTools;
%ignore FileTools::~FileTools;

class FileTools
{
  public:
    static char DIR_SEP;

    FileTools();
    virtual ~FileTools();

    static bool fileExists(const string & filename);
    static bool directoryExists(const string & path);
    static string getFileName(const string & path, char dirSep = DIR_SEP);
    string getParent(const string & path, char dirSep = DIR_SEP);
    static string getExtension(const string & path);
    static vector<string> putStreamIntoVectorOfStrings(istream & input);
    static string getNextLine(istream & in);
};
