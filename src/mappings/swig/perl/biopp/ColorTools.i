%module bpp_colortools
%{
#include "ColorTools.h"
using namespace bpp;
%}

%include "TextTools.i"
%include "Exceptions.i"
%include "RGBColor.i"

using namespace std;

%ignore ColorTools::ColorTools;
%ignore ColorTools::~ColorTools;

class ColorTools
{
  public:
    ColorTools();
    virtual ~ColorTools();

    static vector<RGBColor> gradient(unsigned int n, const RGBColor & low, const RGBColor & high);
    static vector<RGBColor> gradient(unsigned int n, const RGBColor & low, const RGBColor & mid, const RGBColor & high);
    static RGBColor gray(double level);
    static RGBColor cmyk2rgb(double c, double m, double y, double k);
 
    static const RGBColor RED;
    static const RGBColor GREEN;
    static const RGBColor BLUE;
    static const RGBColor BLACK;
    static const RGBColor WHITE;
    static const RGBColor YELLOW;
    static const RGBColor CYAN;
    static const RGBColor MAGENTA;
    static const RGBColor ORANGE;
    
};
