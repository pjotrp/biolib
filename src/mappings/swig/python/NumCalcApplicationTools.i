%module bpp_
%{
#include "NumCalcApplicationTools.h"
using namespace bpp;
%}
%include "StringTokenizer.i"
%include "ApplicationTools.i"
//%include "VectorTools.i"
%include "FunctionTools.i"

class NumCalcApplicationTools
{
  public:
    NumCalcApplicationTools();
    virtual ~NumCalcApplicationTools();

    static vector<int> seqFromString(const string& s, const string& delim = ",", const string& seqdelim = "-");
    static vector<double> getVector(const string& desc) throw (Exception);
    static double getDefaultValue(const ParameterList& pl, const string& name, double x);
    static ParameterGrid* getParameterGrid(map<string, string>& params,const string& suffix = "",bool suffixIsOptional = true,bool warn = true) throw (Exception);
};
