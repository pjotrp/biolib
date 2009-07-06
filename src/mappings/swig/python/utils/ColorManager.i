%module bpp_colormanager
%{
#include "ColorManager.h"
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
  ColorManager();
  virtual ~ColorManager();

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

class XFigColorManager:public ColorManager<unsigned int>
{
public:
  XFigColorManager();
  virtual ~XFigColorManager();

  unsigned int getCode(const RGBColor & color);
  const RGBColor & getColor(unsigned int &code) const throw (Exception);
  vector<unsigned int> getCodes() const;
  vector<RGBColor> getColors() const;
  unsigned int getNumberOfColors() const;

};

} // end of namespace bpp;
