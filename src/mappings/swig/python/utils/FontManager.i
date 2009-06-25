%module bpp_fontmanager
%{
#include "Font.h"
#include <vector>
#include "TextTools.h"
%}

%include "Font.i"
%include "std_vector.i"
%include "TextTools.i"

//%template(doubleList) List<double>;

// From the STL:
using namespace std;

namespace bpp
{

template<class CodeType>
class FontManager
{

public:
  FontManager() {}
  virtual ~FontManager() {}

public:
  virtual CodeType getCode(const Font & font) = 0;
  virtual const Font& getFont(CodeType & code) const throw (Exception) = 0;
  virtual vector<CodeType> getCodes() const = 0;
  virtual vector<Font> getFonts() const = 0;
  virtual unsigned int getNumberOfFonts() const = 0;
};
%template(intFontManager) FontManager<int>;
%template(doubleFontManager) FontManager<double>;
%template(charFontManager) FontManager<char>;

class XFigLaTeXFontManager:
  public FontManager<int>
{
protected:
  vector<Font> _fonts;
  vector<int> _codes;

public:
  XFigLaTeXFontManager()
  {
    // Add "official" font codes, from 0 to 5:
    _codes.push_back(0); _fonts.push_back(Font("Default","Default",12));
    _codes.push_back(1); _fonts.push_back(Font("Roman","",12));
    _codes.push_back(2); _fonts.push_back(Font("Bold","",12));
    _codes.push_back(3); _fonts.push_back(Font("Italic","",12));
    _codes.push_back(4); _fonts.push_back(Font("Sans Serif","",12));
    _codes.push_back(5); _fonts.push_back(Font("Typewriter","",12));
  }

  virtual ~XFigLaTeXFontManager() {}

public:
  int getCode(const Font & font);
  const Font & getFont(int &code) const throw (Exception);
  vector<int> getCodes() const;
  vector<Font> getFonts() const;
  unsigned int getNumberOfFonts() const;
};


class XFigPostscriptFontManager:
  public FontManager<int>
{
protected:
  vector<Font> _fonts;
  vector<int> _codes;

public:
  XFigPostscriptFontManager()
  {
    // Add "official" font codes, from 0 to 5:
    _codes.push_back(-1); _fonts.push_back(Font("Default","Default",12));
    _codes.push_back(0); _fonts.push_back(Font("Times","Roman",12));
    _codes.push_back(1); _fonts.push_back(Font("Times","Italic",12));
    _codes.push_back(2); _fonts.push_back(Font("Times","Bold",12));
    _codes.push_back(3); _fonts.push_back(Font("Times","Bold Italic",12));
    _codes.push_back(4); _fonts.push_back(Font("AvantGarde","Book",12));
    _codes.push_back(5); _fonts.push_back(Font("AvantGarde","Book Oblique",12));
    _codes.push_back(6); _fonts.push_back(Font("AvantGarde","Demi",12));
    _codes.push_back(7); _fonts.push_back(Font("AvantGarde","Demi Oblique",12));
    _codes.push_back(8); _fonts.push_back(Font("Bookman","Light",12));
    _codes.push_back(9); _fonts.push_back(Font("Bookman","Light Italic",12));
    _codes.push_back(10); _fonts.push_back(Font("Bookman","Demi",12));
    _codes.push_back(11); _fonts.push_back(Font("Bookman","Demi Italic",12));
    _codes.push_back(12); _fonts.push_back(Font("Courier","",12));
    _codes.push_back(13); _fonts.push_back(Font("Courier","Oblique",12));
    _codes.push_back(14); _fonts.push_back(Font("Courier","Bold",12));
    _codes.push_back(15); _fonts.push_back(Font("Courier","Bold Oblique",12));
    _codes.push_back(16); _fonts.push_back(Font("Helvetica","",12));
    _codes.push_back(17); _fonts.push_back(Font("Helvetica","Oblique",12));
    _codes.push_back(18); _fonts.push_back(Font("Helvetica","Bold",12));
    _codes.push_back(19); _fonts.push_back(Font("Helvetica","Bold Oblique",12));
    _codes.push_back(20); _fonts.push_back(Font("Helvetica","Narrow",12));
    _codes.push_back(21); _fonts.push_back(Font("Helvetica","Narrow Oblique",12));
    _codes.push_back(22); _fonts.push_back(Font("Helvetica","Narrow Bold",12));
    _codes.push_back(23); _fonts.push_back(Font("Helvetica","Narrow Bold Oblique",12));
    _codes.push_back(24); _fonts.push_back(Font("New Century Schoolbook","Roman",12));
    _codes.push_back(25); _fonts.push_back(Font("New Century Schoolbook","Italic",12));
    _codes.push_back(26); _fonts.push_back(Font("New Century Schoolbook","Bold",12));
    _codes.push_back(27); _fonts.push_back(Font("New Century Schoolbook","Bold Italic",12));
    _codes.push_back(28); _fonts.push_back(Font("Palatino","Roman",12));
    _codes.push_back(29); _fonts.push_back(Font("Palatino","Italic",12));
    _codes.push_back(30); _fonts.push_back(Font("Palatino","Bold",12));
    _codes.push_back(31); _fonts.push_back(Font("Palatino","Bold Italic",12));
    _codes.push_back(32); _fonts.push_back(Font("Symbol","",12));
    _codes.push_back(33); _fonts.push_back(Font("Zapf Chancery Medium","Italic",12));
    _codes.push_back(34); _fonts.push_back(Font("Zapf Dingbats","",12));
  }

  virtual ~XFigPostscriptFontManager() {}

public:
  int getCode(const Font & font);
  const Font & getFont(int &code) const throw (Exception);
  vector<int> getCodes() const;
  vector<Font> getFonts() const;
  unsigned int getNumberOfFonts() const;

};

} // end of namespace.
