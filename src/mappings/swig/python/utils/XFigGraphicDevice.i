%module bpp_xfiggraphicdevice
%{
#include "GraphicDevice.h"
#include "ColorManager.h"
#include "FontManager.h"

// From the STL:
#include <map>
#include <iostream>
%}

%include "GraphicDevice.i"
%include "ColorManager.i"
%include "FontManager.i"
%include "std_map.i"
%include "std_iostream.i"

using namespace std;

namespace bpp
{

class XFigGraphicDevice:
  public virtual GraphicDevice
{
  protected:
    ostream & _out;
    vector<string> _content;
    XFigColorManager _colorManager;
    XFigLaTeXFontManager _LaTeXFontManager;
    XFigPostscriptFontManager _PostscriptFontManager;
    unsigned int _fgColor;
    unsigned int _bgColor;
    int _font; 
    unsigned int _fontSize;
    unsigned int _fontFlag;
    unsigned int _pointSize;
    unsigned int _lineType;
    int _currentLayer;

  public:
    XFigGraphicDevice(ostream & out):
      _out(out),
      _fgColor(0),
      _bgColor(0),
      _font(-1),
      _fontSize(12),
      _fontFlag(FONTFLAG_POSTSCRIPT),
      _pointSize(1)
    {}

    virtual ~XFigGraphicDevice() {}

  public:
    void beginDocument();
    void endDocument();

    void setCurrentForegroundColor(const RGBColor & color);
    void setCurrentBackgroundColor(const RGBColor & color);
    void setCurrentFont(const Font & font);
    void setCurrentPointSize(unsigned int size);
    void setCurrentLineType(short type) throw (Exception);
    void setCurrentLayer(int layerIndex) { _currentLayer = layerIndex; }
    void drawLine(double x1, double y1, double x2, double y2);
    void drawRect(double x, double y, double width, double height, short fill = FILL_EMPTY);
    void drawCircle(double x, double y, double radius, short fill = FILL_EMPTY);
    void drawText(double x, double y, const string & text, short hpos = TEXT_HORIZONTAL_LEFT, short vpos = TEXT_VERTICAL_BOTTOM, double angle = 0);
    void comment(const string & comment);

    //Specific:
    void setFontFlag(unsigned int flag);

  protected:
    int getFillCode(short fill);

  public:
    static const unsigned int FONTFLAG_LATEX;
    static const unsigned int FONTFLAG_POSTSCRIPT;

};

} // end of namespace bpp;
