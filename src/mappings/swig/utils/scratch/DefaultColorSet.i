%module bpp_defaultcolorset
%{
#include "ColorSet.h"
#include "ColorTools.h"
%}

%include "ColorSet.i"
%include "ColorTools.i"

namespace bpp
{

class DefaultColorSet:
  public AbstractColorSet
{
  public:
    DefaultColorSet()
    {
      _colors["black"]   = ColorTools::BLACK;
      _colors["red"]     = ColorTools::RED;
      _colors["green"]   = ColorTools::GREEN;
      _colors["blue"]    = ColorTools::BLUE;
      _colors["yellow"]  = ColorTools::YELLOW;
      _colors["magenta"] = ColorTools::MAGENTA;
      _colors["cyan"]    = ColorTools::CYAN;
      _colors["white"]   = ColorTools::WHITE;
    }
    virtual ~DefaultColorSet() {}

};

} // end of namespace bpp;

