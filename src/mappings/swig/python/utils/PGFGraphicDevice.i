%module bpp_pgfgraphicdevice
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


class PGFGraphicDevice:
  public virtual GraphicDevice
{
  protected:
    ostream & _out;
    string _fgColor;
    string _bgColor;
    Font _font; 
    unsigned int _pointSize;
    short _lineType;
    int _currentLayer;
    vector<string> _content;
    vector<int> _layers;
    double _unit;
    map<const RGBColor, string> _colorIndex;
    unsigned int _colorCount;
    bool _useLayers;

  public:

    PGFGraphicDevice(ostream & out, double unit):
      _out(out),
      _fgColor("black"),
      _bgColor("white"),
      _font(),
      _pointSize(1),
      _unit(unit),
      _colorCount(0)
    {
      _colorIndex[ColorTools::BLACK] = "black";
      _colorIndex[ColorTools::WHITE] = "white";
      _colorIndex[ColorTools::BLUE] = "blue";
      _colorIndex[ColorTools::RED] = "red";
      _colorIndex[ColorTools::GREEN] = "green";
      _colorIndex[ColorTools::YELLOW] = "yellow";
      _colorIndex[ColorTools::CYAN] = "cyan";
      _colorIndex[ColorTools::MAGENTA] = "magenta";
    }

    virtual ~PGFGraphicDevice() {}

  public:
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

} // end of namespace bpp.
