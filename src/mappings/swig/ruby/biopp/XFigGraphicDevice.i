%module bpp_xfiggraphicdevice
%{
#include "XFigGraphicDevice.h"
using namespace bpp;
%}

%include "GraphicDevice.i"
%include "ColorManager.i"
%include "FontManager.i"
%include "std_map.i"
%include "std_iostream.i"

using namespace std;

class XFigGraphicDevice:public virtual GraphicDevice
{
  public:
    XFigGraphicDevice(ostream & out);
    virtual ~XFigGraphicDevice();

    void beginDocument();
    void endDocument();

    void setCurrentForegroundColor(const RGBColor & color);
    void setCurrentBackgroundColor(const RGBColor & color);
    void setCurrentFont(const Font & font);
    void setCurrentPointSize(unsigned int size);
    void setCurrentLineType(short type) throw (Exception);
    void setCurrentLayer(int layerIndex);
    void drawLine(double x1, double y1, double x2, double y2);
    void drawRect(double x, double y, double width, double height, short fill = FILL_EMPTY);
    void drawCircle(double x, double y, double radius, short fill = FILL_EMPTY);
    void drawText(double x, double y, const string & text, short hpos = TEXT_HORIZONTAL_LEFT, short vpos = TEXT_VERTICAL_BOTTOM, double angle = 0);
    void comment(const string & comment);

    //Specific:
    void setFontFlag(unsigned int flag);

    static const unsigned int FONTFLAG_LATEX;
    static const unsigned int FONTFLAG_POSTSCRIPT;
};
