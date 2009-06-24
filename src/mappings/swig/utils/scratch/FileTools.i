%module bpp_filetools
%{
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdio>
//#include <io.h>  // required for directoryExists method
%}

%include "std_string.i"
%include "std_vector.i"
%include "std_iostream.i"
//#include <fstream>
//#include <cstdio>
//#include <io.h>  // required for directoryExists method

using namespace std;

namespace bpp
{

class FileTools
{
	public:
		static char DIR_SEP;
	public:
		FileTools() {}
		virtual ~FileTools() {}
	public:
		static bool fileExists(const string & filename);
		static bool directoryExists(const string & path);
		static string getFileName(const string & path, char dirSep = DIR_SEP);
		string getParent(const string & path, char dirSep = DIR_SEP);
		static string getExtension(const string & path);
		static vector<string> putStreamIntoVectorOfStrings(istream & input);
		static string getNextLine(istream & in);
};

} //end of namespace bpp.
