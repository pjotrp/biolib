%module bpp_pgfgraphicdevice
%{
#include "PGFGraphicDevice.h"
using namespace bpp;
%}

%include "GraphicDevice.i"
%include "ColorTools.i"
//%include "std_map.i"

using namespace std;

class PGFGraphicDevice:public virtual GraphicDevice
{
  public:
    PGFGraphicDevice(ostream & out, double unit);
    virtual ~PGFGraphicDevice();

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
};
