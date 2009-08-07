%module bpp_apptools
%{
#include "ApplicationTools.h"
using namespace bpp;
%}

%include "TextTools.i"
%include "FileTools.i"
%include "StringTokenizer.i"

using namespace std;

%ignore ApplicationTools::ApplicationTools;
%ignore ApplicationTools::~ApplicationTools;

class ApplicationTools
{
  public:
    static ostream * error;
    static ostream * message;
    static ostream * warning;
    static time_t startTime;
    static unsigned int terminalWidth;
    static float terminalSplit;

    ApplicationTools();
    virtual ~ApplicationTools();

    static bool parameterExists(const string & parameterName, map<string, string> & params);
    static double getDoubleParameter(const string & parameterName,map<string, string> & params,double defaultValue,const string & suffix = "",bool suffixIsOptional = true,bool warn = true);
  
    static int getIntParameter(const string & parameterName,map<string, string> & params,int defaultValue,const string & suffix = "",bool suffixIsOptional = true,bool warn = true);
  
    static string getStringParameter(const string & parameterName,map<string, string> & params,const string & defaultValue,const string & suffix = "",bool suffixIsOptional = true,bool warn = true);
    static bool getBooleanParameter(const string & parameterName,map<string, string> & params,bool defaultValue,const string & suffix = "",bool suffixIsOptional = true,bool warn = true);
    template<class T> static T getParameter(const string & parameterName,map<string, string> & params,T defaultValue,const string & suffix = "",bool suffixIsOptional = true,bool warn = true);

    %template(getParameter) getParameter<int>;
    %template(getParameter) getParameter<double>;
    %template(getParameter) getParameter<std::string>;
    %template(getParameter) getParameter<bool>;

    static string getAFilePath(const string & parameter,map<string, string> & params,bool isRequired = true,bool mustExist = true,const string & suffix = "",bool suffixIsOptional = false) throw (Exception);
    template<class T> static vector<T> getVectorParameter(const string & parameterName,map<string, string> & params,char separator,const string & defaultValue,const string & suffix = "",bool suffixIsOptional = true,bool warn = true);
    template<class T> static vector<T> getVectorParameter(const string & parameterName,map<string, string> & params,char separator,char rangeOperator,const string & defaultValue,const string & suffix = "",bool suffixIsOptional = true,bool warn = true);

    %template(getIntVectorParameter) getVectorParameter<int>;
    %template(getDoubleVectorParameter) getVectorParameter<double>;
    //%template(getStringVectorParameter) getVectorParameter<std::string>;
    //%template(getBooleanVectorParameter) getVectorParameter<bool>;

    static void displayMessage(const string & text);
    static void displayError(const string & text);
    static void displayWarning(const string & text);
    static void displayTask(const string & text, bool eof = false);
    static void displayTaskDone();
    
    template<class T> static void displayResult(const string & text, const T & result);

    %template(displayResult) displayResult<int>;
    %template(displayResult) displayResult<double>;
    %template(displayResult) displayResult<std::string>;
    %template(displayResult) displayResult<bool>;

    static void displayGauge(unsigned int iter, unsigned int total, char symbol='>', string mes="");
    static void startTimer();
    static void displayTime(const string & msg);
    static double getTime();

    %extend {
      static ostream* getError() { return ApplicationTools::error; }
      static ostream* getMessage() { return ApplicationTools::message; }
      static ostream* getWarning() { return ApplicationTools::warning; }
    }
};
