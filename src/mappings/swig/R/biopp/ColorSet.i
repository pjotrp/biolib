%module bpp_colorset
%{
#include "ColorSet.h"
using namespace bpp;
%}

%include "RGBColor.i"
%include "MapTools.i"
%include "std_vector.i"

using namespace std;

class ColorSet
{
  public:
    ColorSet();
    virtual ~ColorSet();

    virtual const RGBColor& getColor(const string & name) const throw (Exception) = 0;
    virtual const RGBColor& getColor(unsigned int index) const throw (IndexOutOfBoundsException) = 0;
    virtual vector<string> getColorNames() const = 0;
    virtual unsigned int getNumberOfColors() const = 0;
};

class AbstractColorSet:public ColorSet
{
  public:
    const RGBColor& getColor(const string & name) const throw (Exception);
    const RGBColor& getColor(unsigned int index) const throw (IndexOutOfBoundsException);
    
    vector<string> getColorNames() const;
    unsigned int getNumberOfColors() const;
};
