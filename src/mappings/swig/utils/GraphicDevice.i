%module bpp_graphicdevice
%{
#include "RGBColor.h"
#include "Font.h"
%}

%include "RGBColor.i"
%include "Font.i"

namespace bpp
{


class GraphicDevice
{
  public:
    GraphicDevice() {}
    virtual ~GraphicDevice() {}
  public:
    virtual void beginDocument() = 0;
    virtual void endDocument() = 0;
    virtual void setCurrentForegroundColor(const RGBColor & color) = 0;
    virtual void setCurrentBackgroundColor(const RGBColor & color) = 0;
    virtual void setCurrentFont(const Font & font) = 0;
    virtual void setCurrentPointSize(unsigned int size) = 0;
    virtual void setCurrentLineType(short type) = 0;
    virtual void setCurrentLayer(int layerIndex) = 0;
    virtual void drawLine(double x1, double y1, double x2, double y2) = 0;
    virtual void drawRect(double x, double y, double width, double height, short fill = FILL_EMPTY) = 0;
    virtual void drawCircle(double x, double y, double radius, short fill = FILL_EMPTY) = 0;
    virtual void drawText(double x, double y, const string & text, short hpos = TEXT_HORIZONTAL_LEFT, short vpos = TEXT_VERTICAL_BOTTOM, double angle = 0) = 0;
    virtual void comment(const string & comment) = 0;

  public:
    static short TEXT_HORIZONTAL_CENTER;
    static short TEXT_HORIZONTAL_LEFT;
    static short TEXT_HORIZONTAL_RIGHT;
    static short TEXT_VERTICAL_CENTER;
    static short TEXT_VERTICAL_BOTTOM;
    static short TEXT_VERTICAL_TOP;

    static short FILL_EMPTY;
    static short FILL_FILLED;
    static short FILL_PATTERN;

    static short LINE_SOLID;
    static short LINE_DASHED;
    static short LINE_DOTTED;
};

} // end of namespace bpp.
