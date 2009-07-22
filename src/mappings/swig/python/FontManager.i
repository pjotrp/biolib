%module bpp_fontmanager
%{
#include "FontManager.h"
using namespace bpp;
%}

%include "Font.i"
%include "std_vector.i"
%include "TextTools.i"

//%template(doubleList) List<double>;

// From the STL:
using namespace std;

template<class CodeType>
class FontManager
{

public:
  FontManager();
  virtual ~FontManager();

  virtual CodeType getCode(const Font & font) = 0;
  virtual const Font& getFont(CodeType & code) const throw (Exception) = 0;
  virtual vector<CodeType> getCodes() const = 0;
  virtual vector<Font> getFonts() const = 0;
  virtual unsigned int getNumberOfFonts() const = 0;
};
%template(intFontManager) FontManager<int>;
%template(doubleFontManager) FontManager<double>;
%template(charFontManager) FontManager<char>;

class XFigLaTeXFontManager:public FontManager<int>
{
public:
  XFigLaTeXFontManager();
  virtual ~XFigLaTeXFontManager();

  int getCode(const Font & font);
  const Font & getFont(int &code) const throw (Exception);
  vector<int> getCodes() const;
  vector<Font> getFonts() const;
  unsigned int getNumberOfFonts() const;
};


class XFigPostscriptFontManager:public FontManager<int>
{

public:
  XFigPostscriptFontManager();
  virtual ~XFigPostscriptFontManager();

  int getCode(const Font & font);
  const Font & getFont(int &code) const throw (Exception);
  vector<int> getCodes() const;
  vector<Font> getFonts() const;
  unsigned int getNumberOfFonts() const;

};
