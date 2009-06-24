%module bpp_texttools
%{
#include "Exceptions.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
%}

%include "Exceptions.i"
%include "std_string.i"
%include "std_vector.i"
%include "std_sstream.i"
//#include <iomanip>

using namespace std;

namespace bpp
{


  class TextTools
  {
    public:
      static bool isEmpty(const string & s);
      static string toUpper(const string & s);
      static string toLower(const string & s);
      static bool isWhiteSpaceCharacter(char c);
      static string removeWhiteSpaces (const string & s);
      static string removeFirstWhiteSpaces (const string & s);
      static string removeLastWhiteSpaces (const string & s);
      static string removeSurroundingWhiteSpaces(const string & s);
      static bool isNewLineCharacter(char c);
      static string removeNewLines (const string & s);
      static string removeLastNewLines(const string & s);
      static bool isDecimalNumber(char c);
      static bool isDecimalNumber(const string & s, char dec = '.');
      template<class T> static string toString(T t);
      template<class T> static string toString(T t, int precision);
      template<class T> static T fromString(const string & s);
      static string toString(int i);
      static string toString(char c);
      static string toString(double d, int precision = 6);
      static int toInt(const string & s);
      static double toDouble(const string & s);
      template<class T> static T to(const string & s);
      static string resizeRight(const string & s, unsigned int newSize, char fill = ' ');
      static string resizeLeft(const string & s, unsigned int newSize, char fill = ' ');
      static vector<string> split(const string & s, unsigned int n);
      static string removeSubstrings(const string & s, char blockBeginning, char blockEnding)
        throw (Exception);
      static string removeChar(const string & s, char c);
      static unsigned int count(const string& s, const string& pattern);
      static bool startsWith(const string& s, const string& pattern);
      static bool endsWith(const string& s, const string& pattern);
  };

} //end of namespace bpp.
