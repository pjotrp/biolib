%module bpp_atttools
%{
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
%}

// From the STL:
using namespace std;

namespace bpp 
{

class AttributesTools
{
  
	public:
		AttributesTools() {}
		virtual ~AttributesTools() {}
		static vector<string> getVector(int argc, char * argv[]);
		static map<string, string> getAttributesMap(
			const vector<string> & argv,
			const string & delimiter = "=");
		static void getAttributesMap(
			const vector<string> & argv,
      			map<string, string> & am,
			const string & delimiter = "=");
		static map<string, string> getAttributesMapFromFile(
			const string & file,
			const string & delimiter);
		static void getAttributesMapFromFile(
			const string & file,
      			map<string, string> & params,
			const string & delimiter);
		static void actualizeAttributesMap(
			map<string, string> & attMap,
			const map<string, string> & atts);
		static void resolveVariables(map<string, string> & am,
			char varCode = '$',
			      char varBeg = '(',
			            char varEnd = ')');

	    static map<string, string> parseOptions(int args, char ** argv);

	private:
		static string removeComments(const string & s, const string & begin, const string & end);
};

} //end of namespace bpp.
