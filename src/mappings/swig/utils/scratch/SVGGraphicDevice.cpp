//
// File: SVGGraphicDevice.cpp
// Created by: Julien Dutheil
// Created on: Mon Mar 10 2008
//

/*
Copyright or © or Copr. CNRS, (November 17, 2004)

This software is a computer program whose purpose is to provide utilitary
classes. This file belongs to the Bio++ Project.

This software is governed by the CeCILL  license under French law and
abiding by the rules of distribution of free software.  You can  use, 
modify and/ or redistribute the software under the terms of the CeCILL
license as circulated by CEA, CNRS and INRIA at the following URL
"http://www.cecill.info". 

As a counterpart to the access to the source code and  rights to copy,
modify and redistribute granted by the license, users are provided only
with a limited warranty  and the software's author,  the holder of the
economic rights,  and the successive licensors  have only  limited
liability. 

In this respect, the user's attention is drawn to the risks associated
with loading,  using,  modifying and/or developing or reproducing the
software by the user in light of its specific status of free software,
that may mean  that it is complicated to manipulate,  and  that  also
therefore means  that it is reserved for developers  and  experienced
professionals having in-depth computer knowledge. Users are therefore
encouraged to load and test the software's suitability as regards their
requirements in conditions enabling the security of their systems and/or 
data to be ensured and,  more generally, to use and operate it in the 
same conditions as regards security. 

The fact that you are presently reading this means that you have had
knowledge of the CeCILL license and that you accept its terms.
*/

#include "SVGGraphicDevice.h"

using namespace bpp;

void SVGGraphicDevice::beginDocument()
{
  _layers.clear();
}

void SVGGraphicDevice::endDocument()
{
  //Header:
  _out << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
  _out << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"" << endl;
  _out << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">" << endl;
  _out << "<svg width=\"100%\" height=\"100%\" version=\"1.1\"" << endl;
  _out << " xmlns=\"http://www.w3.org/2000/svg\"" << endl;
  if(_inkscapeEnabled)
    _out << " xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"";
  _out << " >" << endl;
  
  for(map<int, vector<string> >::iterator it = _layers.begin(); it != _layers.end(); it++)
  {
    _out << "<g id=\"layer" << it->first << "\"";
    if(_inkscapeEnabled)
    {
      _out << " inkscape:groupmode=\"layer\"";
    }
    _out << " >" << endl;
    vector<string> * v = &it->second;
    for(unsigned int i = 0; i < v->size(); i++)
    {
      _out << (*v)[i] << endl;
    }
    _out << "</g>" << endl;
  }
  
  _out << "</svg>" << endl;
}

void SVGGraphicDevice::setCurrentForegroundColor(const RGBColor & color)
{
  _fgColor = color;
}

void SVGGraphicDevice::setCurrentBackgroundColor(const RGBColor & color)
{
  _bgColor = color;
}

void SVGGraphicDevice::setCurrentFont(const Font & font)
{
  _font = font;
}

void SVGGraphicDevice::drawLine(double x1, double y1, double x2, double y2)
{
  string style = "stroke:" + colorToText(_fgColor) + ";stroke-width:" + TextTools::toString(_pointSize);
  if(_lineType == LINE_DASHED)
    style += ";stroke-dasharray:4,4";
  else if(_lineType == LINE_DOTTED)
    style += ";stroke-dasharray:1,2";
  ostringstream oss;
  oss << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" style=\"" << style << "\" />";
  _layers[_currentLayer].push_back(oss.str());
}
 
void SVGGraphicDevice::drawRect(double x, double y, double width, double height, short fill)
{
  string style = "stroke:" + colorToText(_fgColor) + ";stroke-width:" + TextTools::toString(_pointSize);
  if(fill == FILL_FILLED)
  {
    style += ";fill:" + colorToText(_bgColor);
  }
  ostringstream oss;
  oss << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\" style=\"" << style << "\" />";
  _layers[_currentLayer].push_back(oss.str());
}

void SVGGraphicDevice::drawCircle(double x, double y, double radius, short fill)
{
  string style = "stroke:" + colorToText(_fgColor) + ";stroke-width:" + TextTools::toString(_pointSize);
  if(fill == FILL_FILLED)
  {
    style += ";fill:" + colorToText(_bgColor);
  }
  ostringstream oss;
  oss << "<rect cx=\"" << x << "\" cy=\"" << y << "\" cr=\"" << radius << "\" style=\"" << style << "\" />";
  _layers[_currentLayer].push_back(oss.str());
}

void SVGGraphicDevice::drawText(double x, double y, const string & text, short hpos, short vpos, double angle)
{
  string style = "font-family:" + _font.getFamily() + ";font-style:" + _font.getType() + ";font-size:" + TextTools::toString(_font.getSize()) + "px";
  style += ";dominant-baseline:";
  if(vpos == TEXT_VERTICAL_BOTTOM)
    style += "before-edge";
  else if(vpos == TEXT_VERTICAL_TOP)
    style += "after-edge";
  else if(vpos == TEXT_VERTICAL_CENTER)
    style += "middle";
  else throw Exception("SVGGraphicDevice::drawText. Invalid vertical alignment option.");
  style += ";text-anchor:";
  if(hpos == TEXT_HORIZONTAL_LEFT)
    style += "start";
  else if(hpos == TEXT_HORIZONTAL_RIGHT)
    style += "end";
  else if(hpos == TEXT_HORIZONTAL_CENTER)
    style += "middle";
  else throw Exception("SVGGraphicDevice::drawText. Invalid horizontal alignment option.");
  style += ";fill:" + colorToText(_fgColor);

  ostringstream oss;
  oss << "<text x=\"" << x << "\" y=\"" << y << "\" rotate=\"" << angle << "\" style=\"" << style << "\" >" << text << "</text>";
  _layers[_currentLayer].push_back(oss.str());
}

