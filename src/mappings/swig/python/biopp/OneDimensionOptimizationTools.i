%module bpp_
%{
#include "OneDimensionOptimizationTools.h"
using namespace bpp;
%}
%include "Functions.i"
%include "DirectionFunction.i"

class Point
{    
  public: 
    Point();
    Point(double x, double f): x(x), f(f);
    virtual ~Point();

    void set(double x, double f);

    double x;
    double f;      
};

class Bracket
{  
  public: 
    Bracket();
    virtual ~Bracket();
  public: 
    void setA(double xa, double fa);
    void setB(double xb, double fb);
    void setC(double xc, double fc);
  public:
    Point a, b, c;
};

%ignore OneDimensionOptimizationTools::OneDimensionOptimizationTools;
%ignore OneDimensionOptimizationTools::~OneDimensionOptimizationTools;

class OneDimensionOptimizationTools
{
  public:
    OneDimensionOptimizationTools();
    virtual ~OneDimensionOptimizationTools();

    static Bracket bracketMinimum(double a, double b, Function * function, ParameterList parameters);
    static unsigned int lineMinimization(DirectionFunction & f1dim, ParameterList & parameters, vector<double> & xi, double tolerance, ostream * profiler = NULL, ostream * messenger = NULL, int verbose = 2);

    static double GLIMIT;
};
