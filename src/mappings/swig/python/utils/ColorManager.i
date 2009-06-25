%module bpp_colormanager
%{
#include "RGBColor.h"
#include "ColorTools.h"
#include "TextTools.h"
#include <vector>
%}

%include "RGBColor.i"
%include "ColorTools.i"
%include "TextTools.i"
%include "std_vector.i"

using namespace std;

namespace bpp
{

template<class CodeType>
class ColorManager
{
public:
  ColorManager() {}
  virtual ~ColorManager() {}

public:
  virtual CodeType getCode(const RGBColor & color) = 0;
  virtual const RGBColor& getColor(CodeType & code) const throw (Exception) = 0;
  virtual vector<CodeType> getCodes() const = 0;
  virtual vector<RGBColor> getColors() const = 0;
  virtual unsigned int getNumberOfColors() const = 0;
};

%template(intColorManager) ColorManager<int>;
%template(uintColorManager) ColorManager<unsigned int>;
%template(doubleColorManager) ColorManager<double>;
%template(charColorManager) ColorManager<char>;

class XFigColorManager:
  public ColorManager<unsigned int>
{
protected:
  unsigned int _currentCode;
  vector<RGBColor> _colors;
  vector<unsigned int> _codes;

public:
  XFigColorManager(): _currentCode(31)
  {
    // Add "official" color codes, from 0 to 31:
    _codes.push_back(0); _colors.push_back(ColorTools::BLACK);
    _codes.push_back(1); _colors.push_back(ColorTools::BLUE);
    _codes.push_back(2); _colors.push_back(ColorTools::GREEN);
    _codes.push_back(3); _colors.push_back(ColorTools::CYAN);
    _codes.push_back(4); _colors.push_back(ColorTools::RED);
    _codes.push_back(5); _colors.push_back(ColorTools::MAGENTA);
    _codes.push_back(6); _colors.push_back(ColorTools::YELLOW);
    _codes.push_back(7); _colors.push_back(ColorTools::WHITE);
    _codes.push_back(8); _colors.push_back(RGBColor(0,0,140));
    _codes.push_back(9); _colors.push_back(RGBColor(0,0,173));
    _codes.push_back(10); _colors.push_back(RGBColor(0,0,206));
    _codes.push_back(11); _colors.push_back(RGBColor(132,207,205));
    _codes.push_back(12); _colors.push_back(RGBColor(0,142,0));
    _codes.push_back(13); _colors.push_back(RGBColor(0,174,0));
    _codes.push_back(14); _colors.push_back(RGBColor(0,207,0));
    _codes.push_back(15); _colors.push_back(RGBColor(0,142,140));
    _codes.push_back(16); _colors.push_back(RGBColor(0,174,173));
    _codes.push_back(17); _colors.push_back(RGBColor(0,207,206));
    _codes.push_back(18); _colors.push_back(RGBColor(140,0,0));
    _codes.push_back(19); _colors.push_back(RGBColor(173,0,0));
    _codes.push_back(20); _colors.push_back(RGBColor(206,0,0));
    _codes.push_back(21); _colors.push_back(RGBColor(140,0,140));
    _codes.push_back(22); _colors.push_back(RGBColor(173,0,173));
    _codes.push_back(23); _colors.push_back(RGBColor(206,0,206));
    _codes.push_back(24); _colors.push_back(RGBColor(132,48,0));
    _codes.push_back(25); _colors.push_back(RGBColor(156,65,0));
    _codes.push_back(26); _colors.push_back(RGBColor(189,97,0));
    _codes.push_back(27); _colors.push_back(RGBColor(255,130,132));
    _codes.push_back(28); _colors.push_back(RGBColor(255,158,156));
    _codes.push_back(29); _colors.push_back(RGBColor(255,190,189));
    _codes.push_back(30); _colors.push_back(RGBColor(255,223,222));
    _codes.push_back(31); _colors.push_back(RGBColor(255,215,0));
  }
  virtual ~XFigColorManager() {}

public:
  unsigned int getCode(const RGBColor & color)
  {
    for(unsigned int i = 0; i < _colors.size(); i++)
    {
      if(_colors[i] == color)
      {
        return _codes[i];
      }
    }
    _currentCode++;
    _colors.push_back(color);
    _codes.push_back(_currentCode);
    return _currentCode;
  }
  const RGBColor & getColor(unsigned int &code) const throw (Exception)
  {
    for(unsigned int i = 0; i < _codes.size(); i++)
    {
      if(_codes[i] == code)
      {
        return _colors[i];
      }
    }
    throw Exception("XFigColorManager::getColor. No color associated to this code: " + TextTools::toString(code));
  }
  vector<unsigned int> getCodes() const { return _codes; }
  vector<RGBColor> getColors() const { return _colors; }
  unsigned int getNumberOfColors() const { return _colors.size(); }

};

} // end of namespace bpp;
