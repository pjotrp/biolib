%module bpp_svggraphicdevice
%{
#include "SVGGraphicDevice.h"
using namespace bpp;
%}

%include "GraphicDevice.i"
%include "ColorTools.i"
%include "std_map.i"

using namespace std;

class SVGGraphicDevice:public virtual GraphicDevice
{
  public:
    SVGGraphicDevice(ostream & out, bool inkscapeEnabled = false);
    virtual ~SVGGraphicDevice();

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

    static string colorToText(const RGBColor & color);
};
