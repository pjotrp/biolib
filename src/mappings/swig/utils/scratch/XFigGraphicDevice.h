//
// File: XFigGraphicDevice.h
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

#ifndef _XFIGGRAPHICDEVICE_H_
#define _XFIGGRAPHICDEVICE_H_

#include "GraphicDevice.h"
#include "ColorManager.h"
#include "FontManager.h"

// From the STL:
#include <map>
#include <iostream>
using namespace std;

namespace bpp
{

/**
 * @brief XFig plotting format.
 */
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
    void setCurrentPointSize(unsigned int size) { _pointSize = size; }
    void setCurrentLineType(short type) throw (Exception)
    { 
      if(type == LINE_SOLID) _lineType = 0;
      else if(type == LINE_DASHED) _lineType = 1;
      else if(type == LINE_DOTTED) _lineType = 2;
      else throw Exception("XFigGraphicDevice::setCurrentLineType. Unknown line type: " + TextTools::toString(type));
    }
    void setCurrentLayer(int layerIndex) { _currentLayer = layerIndex; }
    void drawLine(double x1, double y1, double x2, double y2);
    void drawRect(double x, double y, double width, double height, short fill = FILL_EMPTY);
    void drawCircle(double x, double y, double radius, short fill = FILL_EMPTY);
    void drawText(double x, double y, const string & text, short hpos = TEXT_HORIZONTAL_LEFT, short vpos = TEXT_VERTICAL_BOTTOM, double angle = 0);
    void comment(const string & comment)
    {
      _content.push_back("#" + comment);
    }

    //Specific:
    void setFontFlag(unsigned int flag) { _fontFlag = flag; }

  protected:
    int getFillCode(short fill);

  public:
    static const unsigned int FONTFLAG_LATEX;
    static const unsigned int FONTFLAG_POSTSCRIPT;

};

} // end of namespace bpp;

#endif //_XFIGGRAPHICDEVICE_H_


