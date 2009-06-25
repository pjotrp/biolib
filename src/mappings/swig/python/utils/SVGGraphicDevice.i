%module bpp_svggraphicdevice
%{
#include "GraphicDevice.h"
#include "ColorTools.h"
#include <map>
%}

%include "GraphicDevice.i"
%include "ColorTools.i"
%include "std_map.i"

using namespace std;

namespace bpp
{

class SVGGraphicDevice:
  public virtual GraphicDevice
{
  protected:
    ostream & _out;
    RGBColor _fgColor;
    RGBColor _bgColor;
    Font _font; 
    unsigned int _pointSize;
    short _lineType;
    int _currentLayer;
    map<int, vector<string>, greater<int> > _layers; //Layer display as in xfig
    bool _inkscapeEnabled;

  public:
    SVGGraphicDevice(ostream & out, bool inkscapeEnabled = false):
      _out(out),
      _fgColor(ColorTools::BLACK),
      _bgColor(ColorTools::WHITE),
      _font(),
      _pointSize(1),
      _inkscapeEnabled(inkscapeEnabled)
    {}

    virtual ~SVGGraphicDevice() {}

  public:
    void beginDocument();
    void endDocument();

    void setCurrentForegroundColor(const RGBColor & color);
    void setCurrentBackgroundColor(const RGBColor & color);
    void setCurrentFont(const Font & font);
    void setCurrentPointSize(unsigned int size) { _pointSize = size; }
    void setCurrentLineType(short type) throw (Exception);
    void setCurrentLayer(int layerIndex);
    void drawLine(double x1, double y1, double x2, double y2);
    void drawRect(double x, double y, double width, double height, short fill = FILL_EMPTY);
    void drawCircle(double x, double y, double radius, short fill = FILL_EMPTY);
    void drawText(double x, double y, const string & text, short hpos = TEXT_HORIZONTAL_LEFT, short vpos = TEXT_VERTICAL_BOTTOM, double angle = 0);
    void comment(const string & comment);

  public:
    static string colorToText(const RGBColor & color);
};

} // end of namespace bpp.
