%module bpp_apptools
%{
#include "TextTools.h"
#include "FileTools.h"
#include "StringTokenizer.h"

// From the STL:
#include <map>
#include <vector>
#include <iostream>
#include <ctime>
%}

using namespace std;

namespace bpp
{
class ApplicationTools
{
  public:
    static ostream * error;
    static ostream * message;
    static ostream * warning;
    static time_t startTime;
    static unsigned int terminalWidth;
    static float terminalSplit;
  
  public:
    ApplicationTools();
    virtual ~ApplicationTools();
  
  public:
    static bool parameterExists(const string & parameterName, map<string, string> & params);
    static double getDoubleParameter(
      const string & parameterName,
      map<string, string> & params,
      double defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true);
  
    static int getIntParameter(
      const string & parameterName,
      map<string, string> & params,
      int defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true);
  
    static string getStringParameter(
      const string & parameterName,
      map<string, string> & params,
      const string & defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true);
    static bool getBooleanParameter(
      const string & parameterName,
      map<string, string> & params,
      bool defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true);
    template<class T> static T getParameter(
      const string & parameterName,
      map<string, string> & params,
      T defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true)
    {
      T tParam = defaultValue;
      if(parameterExists(parameterName + suffix, params))
      {
        tParam = TextTools::to<T>(params[parameterName + suffix]);
      }
      else if(suffixIsOptional && parameterExists(parameterName, params))
      {
        tParam = TextTools::to<T>(params[parameterName]);
      } else if(warn)
      {
        displayWarning("Parameter " + parameterName + suffix + " not specified. Default used instead: " + TextTools::toString(defaultValue));
      }
      return tParam;
    }
  
    static string getAFilePath(
      const string & parameter,
      map<string, string> & params,
      bool isRequired = true,
      bool mustExist = true,
      const string & suffix = "",
      bool suffixIsOptional = false) throw (Exception);
    template<class T> static vector<T> getVectorParameter(
      const string & parameterName,
      map<string, string> & params,
      char separator,
      const string & defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true)
    {
      string s = getStringParameter(parameterName, params, defaultValue, suffix, suffixIsOptional, warn);
      StringTokenizer st(s, TextTools::toString(separator));
      unsigned int n = st.numberOfRemainingTokens();
      vector<T> v(n);
      for(unsigned int i = 0; i < n; i++)
      {
        v[i] = TextTools::fromString<T>(st.nextToken());
      }
      return v;
    }
    template<class T> static vector<T> getVectorParameter(
      const string & parameterName,
      map<string, string> & params,
      char separator,
      char rangeOperator,
      const string & defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true)
    {
      string s = getStringParameter(parameterName, params, defaultValue, suffix, suffixIsOptional, warn);
      StringTokenizer st(s, TextTools::toString(separator));
      unsigned int n = st.numberOfRemainingTokens();
      vector<T> v;
      for(unsigned int i = 0; i < n; i++)
      {
        string s = st.nextToken();
        string::size_type i = s.find(rangeOperator);
        if(i == string::npos)
          v.push_back(TextTools::fromString<T>(s));
        else
        {
          T d1 = TextTools::fromString<T>(s.substr(0, i));
          T d2 = TextTools::fromString<T>(s.substr(i+1));
          for(T j = d1; j < d2; j++)
          {
            v.push_back(j);
          }
          v.push_back(d2);
        }
      }
      return v;
    }

    static void displayMessage(const string & text);
    static void displayError(const string & text);
    static void displayWarning(const string & text);
    static void displayTask(const string & text, bool eof = false);
    static void displayTaskDone();
    
    template<class T>
    static void displayResult(const string & text, const T & result)
    {
      displayMessage(TextTools::resizeRight(text, (unsigned int) (terminalWidth * terminalSplit - 1), '.') + ": " + TextTools::toString<T>(result));
    }
    static void displayGauge(unsigned int iter, unsigned int total, char symbol='>', string mes="");
    static void startTimer()
    {
      time(&startTime);
    }
    static void displayTime(const string & msg);
    static double getTime();
};

} //end of namespace bpp.
