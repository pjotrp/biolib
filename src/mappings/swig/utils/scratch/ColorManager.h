//
// File: ColorManager.h
// Created by: Julien Dutheil
// Created on: Mon May 08 2006
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

#ifndef _COLORMANAGER_H_
#define _COLORMANAGER_H_

#include "RGBColor.h"
#include "ColorTools.h"
#include "TextTools.h"

// From the STL:
#include <vector>
using namespace std;

namespace bpp
{

/**
 * @brief Associate special colors to a code.
 *
 * Instances of this interface are used in some vector format.
 */
template<class CodeType>
class ColorManager
{
public:
  ColorManager() {}
  virtual ~ColorManager() {}

public:

  /**
   * @param color The color to look for.
   * @return The code associated to a given color.
   */
  virtual CodeType getCode(const RGBColor & color) = 0;
  
  /**
   * @param code The code to look for.
   * @return The color associated to a given code.
   * @throw exception if the code is not valid.
   */
  virtual const RGBColor& getColor(CodeType & code) const throw (Exception) = 0;

  /**
   * @return All valid codes.
   */
  virtual vector<CodeType> getCodes() const = 0;
  
  /**
   * @return All available colors.
   */
  virtual vector<RGBColor> getColors() const = 0;

  /**
   * @return The total number of colors available.
   */
  virtual unsigned int getNumberOfColors() const = 0;
};





/**
 * @brief Color manager for the XFig format.
 *
 * Default colors are coded from 0 to 31.
 * New colors may be added from code 32.
 */
class XFigColorManager:
  public ColorManager<unsigned int>
{
protected:
  unsigned int _currentCode;
  vector<RGBColor> _colors;
  vector<unsigned int> _codes;

public:
  XFigColorManager(): _currentCode(31)
  {
    // Add "official" color codes, from 0 to 31:
    _codes.push_back(0); _colors.push_back(ColorTools::BLACK);
    _codes.push_back(1); _colors.push_back(ColorTools::BLUE);
    _codes.push_back(2); _colors.push_back(ColorTools::GREEN);
    _codes.push_back(3); _colors.push_back(ColorTools::CYAN);
    _codes.push_back(4); _colors.push_back(ColorTools::RED);
    _codes.push_back(5); _colors.push_back(ColorTools::MAGENTA);
    _codes.push_back(6); _colors.push_back(ColorTools::YELLOW);
    _codes.push_back(7); _colors.push_back(ColorTools::WHITE);
    _codes.push_back(8); _colors.push_back(RGBColor(0,0,140));
    _codes.push_back(9); _colors.push_back(RGBColor(0,0,173));
    _codes.push_back(10); _colors.push_back(RGBColor(0,0,206));
    _codes.push_back(11); _colors.push_back(RGBColor(132,207,205));
    _codes.push_back(12); _colors.push_back(RGBColor(0,142,0));
    _codes.push_back(13); _colors.push_back(RGBColor(0,174,0));
    _codes.push_back(14); _colors.push_back(RGBColor(0,207,0));
    _codes.push_back(15); _colors.push_back(RGBColor(0,142,140));
    _codes.push_back(16); _colors.push_back(RGBColor(0,174,173));
    _codes.push_back(17); _colors.push_back(RGBColor(0,207,206));
    _codes.push_back(18); _colors.push_back(RGBColor(140,0,0));
    _codes.push_back(19); _colors.push_back(RGBColor(173,0,0));
    _codes.push_back(20); _colors.push_back(RGBColor(206,0,0));
    _codes.push_back(21); _colors.push_back(RGBColor(140,0,140));
    _codes.push_back(22); _colors.push_back(RGBColor(173,0,173));
    _codes.push_back(23); _colors.push_back(RGBColor(206,0,206));
    _codes.push_back(24); _colors.push_back(RGBColor(132,48,0));
    _codes.push_back(25); _colors.push_back(RGBColor(156,65,0));
    _codes.push_back(26); _colors.push_back(RGBColor(189,97,0));
    _codes.push_back(27); _colors.push_back(RGBColor(255,130,132));
    _codes.push_back(28); _colors.push_back(RGBColor(255,158,156));
    _codes.push_back(29); _colors.push_back(RGBColor(255,190,189));
    _codes.push_back(30); _colors.push_back(RGBColor(255,223,222));
    _codes.push_back(31); _colors.push_back(RGBColor(255,215,0));
  }
  virtual ~XFigColorManager() {}

public:
  unsigned int getCode(const RGBColor & color)
  {
    for(unsigned int i = 0; i < _colors.size(); i++)
    {
      if(_colors[i] == color)
      {
        return _codes[i];
      }
    }
    _currentCode++;
    _colors.push_back(color);
    _codes.push_back(_currentCode);
    return _currentCode;
  }
  const RGBColor & getColor(unsigned int &code) const throw (Exception)
  {
    for(unsigned int i = 0; i < _codes.size(); i++)
    {
      if(_codes[i] == code)
      {
        return _colors[i];
      }
    }
    throw Exception("XFigColorManager::getColor. No color associated to this code: " + TextTools::toString(code));
  }
  vector<unsigned int> getCodes() const { return _codes; }
  vector<RGBColor> getColors() const { return _colors; }
  unsigned int getNumberOfColors() const { return _colors.size(); }

};

} // end of namespace bpp;

#endif //_COLORMANAGER_H_

