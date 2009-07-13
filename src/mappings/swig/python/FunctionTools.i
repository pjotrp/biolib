%module bpp_
%{
#include "FunctionTools.h"
%}
%include "Functions.i"
%include "VectorTools.i"
namespace bpp
{
class ParameterGrid
{
  public:
    void addDimension(const string& name, const Vdouble& values) throw (Exception);
    const vector<string>& getDimensionNames() const;
    const string& getDimensionName(unsigned int i) const throw (IndexOutOfBoundsException);
    unsigned int getNumberOfDimensions() const;
    unsigned int getTotalNumberOfPoints() const;
    const VVdouble& getPoints() const;
    const Vdouble& getPointsForDimension(unsigned int i) const throw (IndexOutOfBoundsException);
    const Vdouble& getPointsForDimension(const string& name) const throw (Exception);
};

class FunctionTools
{
  public:
    static VVdouble* computeGrid(Function& function,const ParameterGrid& grid) throw (Exception);
};
} 
