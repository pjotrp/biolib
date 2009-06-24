//
// File: XFigGraphicDevice.cpp
// Created by: Julien Dutheil
// Created on: Mon Mar 03 2008
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

#include "XFigGraphicDevice.h"

using namespace bpp;

const unsigned int XFigGraphicDevice::FONTFLAG_LATEX = 0;
const unsigned int XFigGraphicDevice::FONTFLAG_POSTSCRIPT = 4;

void XFigGraphicDevice::beginDocument()
{
  _content.clear();
}

void XFigGraphicDevice::endDocument()
{
  //Print to file:
  //Header:
  _out << "#FIG 3.2 Produced by TreeMap version 0.1" << endl;
  _out << "Portrait" << endl;
  _out << "Flush left" << endl;
  _out << "Metric" << endl;
  _out << "A4" << endl;
  _out << "100" << endl;
  _out << "Single" << endl;
  _out << "0" << endl;
  //out << "254 2" << endl; // 1fig unit = 0.1mm
  _out << "72 2" << endl; // 1fig unit = 1pt

  // Color definitions:
  _out << "#Color definitions:" << endl; 
  vector<unsigned int> codes = _colorManager.getCodes();
  vector<RGBColor> colors    = _colorManager.getColors();
  for(unsigned int i = 32; i < _colorManager.getNumberOfColors(); i++)
  {
    string hexCode = colors[i].toHex();
    _out << "0 " << codes[i] << " " << hexCode << endl;
  }

  // Print content:
  for(unsigned int i = 0; i < _content.size(); i++)
  {
    _out << _content[i] << endl;
  }
}

void XFigGraphicDevice::setCurrentForegroundColor(const RGBColor & color)
{
  _fgColor = _colorManager.getCode(color);
}

void XFigGraphicDevice::setCurrentBackgroundColor(const RGBColor & color)
{
  _bgColor = _colorManager.getCode(color);
}

void XFigGraphicDevice::setCurrentFont(const Font & font)
{
  if(_fontFlag == FONTFLAG_LATEX)
    _font = _LaTeXFontManager.getCode(font);
  else if(_fontFlag == FONTFLAG_POSTSCRIPT)
    _font = _PostscriptFontManager.getCode(font);
  else
    _font = 0;
  _fontSize = font.getSize();
}

void XFigGraphicDevice::drawLine(double x1, double y1, double x2, double y2)
{
  ostringstream oss;
  oss << "2 1 " << _lineType << " " << _pointSize
      << " " << _fgColor
      << " " << _bgColor
      << " " << _currentLayer
      << " " << "-1 -1 -1 0 0 0 0 0 2" << endl;
  oss << x1 << " " << y1 << endl;
  oss << x2 << " " << y2;
  _content.push_back(oss.str());
}
 
void XFigGraphicDevice::drawRect(double x, double y, double width, double height, short fill)
{
  ostringstream oss;
  oss << "2 2 0 " << _pointSize
      << " " << _fgColor
      << " " << _bgColor
      << " " << _currentLayer
      << " " << "-1"
      << " " << getFillCode(fill) << " -1 0 0 0 0 0 5" << endl;
  oss << x << " " << y << endl;
  oss << x + width << " " << y << endl;
  oss << x + width << " " << y + height << endl;
  oss << x << " " << y + height << endl;
  oss << x << " " << y;
  _content.push_back(oss.str());
}

void XFigGraphicDevice::drawCircle(double x, double y, double radius, short fill)
{
  ostringstream oss;
  oss << "1 3 0 " << _pointSize
      << " " << _fgColor
      << " " << _bgColor
      << " " << _currentLayer
      << " " << "-1"
      << " " << getFillCode(fill) << " -1 1 0 "
      << x << " " << y << " "
      << radius << " " << radius << " "
      << x + radius << " " << y << " "
      << x + radius << " " << y << endl;
  _content.push_back(oss.str());
}

void XFigGraphicDevice::drawText(double x, double y, const string & text, short hpos, short vpos, double angle)
{
  int xrel = (int)x;
  short sub = 0;
  if(hpos == TEXT_HORIZONTAL_CENTER) 
  {
    sub = 1;
  }
  if(hpos == TEXT_HORIZONTAL_RIGHT)
  {
    sub = 2;
  }
  int yrel = (int)(y - 1);
  if(vpos == TEXT_VERTICAL_CENTER) yrel = (int)(y + _fontSize / 2 - 1); 
  if(vpos == TEXT_VERTICAL_TOP) yrel = (int)(y - _fontSize); 
  ostringstream oss;
  oss << "4 " << sub << " " << _fgColor << " " << 50 << " " << -1 << " " << _font << " " << _fontSize << " " 
      << angle << " " << _fontFlag << " " << -1 << " " << -1 << " " << xrel << " " << yrel << " " << text << "\\001";
  _content.push_back(oss.str());
}

int XFigGraphicDevice::getFillCode(short fill)
{
  if(fill == FILL_EMPTY) return -1;
  if(fill == FILL_FILLED) return 20;
  if(fill == FILL_PATTERN)
  {
    //TODO: define a field names _currentPattern, etc.
  }
  //Temp:
  return 20;
}

