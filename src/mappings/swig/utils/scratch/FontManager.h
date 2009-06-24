//
// File: FontManager.h
// Created by: Julien Dutheil
// Created on: Sat Mar 08 2008
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

#ifndef _FONTMANAGER_H_
#define _FONTMANAGER_H_

#include "Font.h"

// From the STL:
#include <vector>
using namespace std;

#include "TextTools.h"

namespace bpp
{

/**
 * @brief Associate special fonts to a code.
 *
 * Instances of this interface are used in some vector format.
 */
template<class CodeType>
class FontManager
{
public:
  FontManager() {}
  virtual ~FontManager() {}

public:

  /**
   * @param font The font to look for.
   * @return The code associated to a given font.
   */
  virtual CodeType getCode(const Font & font) = 0;

  /**
   * @param code The code to look for.
   * @return The font associated to a given code.
   * @throw exception if the code is not valid.
   */
  virtual const Font& getFont(CodeType & code) const throw (Exception) = 0;

  /**
   * @return All valid codes.
   */
  virtual vector<CodeType> getCodes() const = 0;

  /**
   * @return All available fonts.
   */
  virtual vector<Font> getFonts() const = 0;

  /**
   * @return The total number of fonts available.
   */
  virtual unsigned int getNumberOfFonts() const = 0;
};






/**
 * @brief LaTeX font manager for the XFig format.
 */
class XFigLaTeXFontManager:
  public FontManager<int>
{
protected:
  vector<Font> _fonts;
  vector<int> _codes;

public:
  XFigLaTeXFontManager()
  {
    // Add "official" font codes, from 0 to 5:
    _codes.push_back(0); _fonts.push_back(Font("Default","Default",12));
    _codes.push_back(1); _fonts.push_back(Font("Roman","",12));
    _codes.push_back(2); _fonts.push_back(Font("Bold","",12));
    _codes.push_back(3); _fonts.push_back(Font("Italic","",12));
    _codes.push_back(4); _fonts.push_back(Font("Sans Serif","",12));
    _codes.push_back(5); _fonts.push_back(Font("Typewriter","",12));
  }

  virtual ~XFigLaTeXFontManager() {}

public:
  int getCode(const Font & font)
  {
    for(unsigned int i = 0; i < _fonts.size(); i++)
    {
      if(_fonts[i].getFamily() == font.getFamily() && _fonts[i].getType() == font.getType())
      {
        return _codes[i];
      }
    }
    throw Exception("XFigLaTeXFontManager::getCode. Unknown font: " + font.toString());
  }
  const Font & getFont(int &code) const throw (Exception)
  {
    for(unsigned int i = 0; i < _codes.size(); i++)
    {
      if(_codes[i] == code)
      {
        return _fonts[i];
      }
    }
    throw Exception("XFigLaTeXFontManager::getColor. No font associated to this code: " + TextTools::toString(code));
  }
  vector<int> getCodes() const { return _codes; }
  vector<Font> getFonts() const { return _fonts; }
  unsigned int getNumberOfFonts() const { return _fonts.size(); }

};





/**
 * @brief Postscript font manager for the XFig format.
 */
class XFigPostscriptFontManager:
  public FontManager<int>
{
protected:
  vector<Font> _fonts;
  vector<int> _codes;

public:
  XFigPostscriptFontManager()
  {
    // Add "official" font codes, from 0 to 5:
    _codes.push_back(-1); _fonts.push_back(Font("Default","Default",12));
    _codes.push_back(0); _fonts.push_back(Font("Times","Roman",12));
    _codes.push_back(1); _fonts.push_back(Font("Times","Italic",12));
    _codes.push_back(2); _fonts.push_back(Font("Times","Bold",12));
    _codes.push_back(3); _fonts.push_back(Font("Times","Bold Italic",12));
    _codes.push_back(4); _fonts.push_back(Font("AvantGarde","Book",12));
    _codes.push_back(5); _fonts.push_back(Font("AvantGarde","Book Oblique",12));
    _codes.push_back(6); _fonts.push_back(Font("AvantGarde","Demi",12));
    _codes.push_back(7); _fonts.push_back(Font("AvantGarde","Demi Oblique",12));
    _codes.push_back(8); _fonts.push_back(Font("Bookman","Light",12));
    _codes.push_back(9); _fonts.push_back(Font("Bookman","Light Italic",12));
    _codes.push_back(10); _fonts.push_back(Font("Bookman","Demi",12));
    _codes.push_back(11); _fonts.push_back(Font("Bookman","Demi Italic",12));
    _codes.push_back(12); _fonts.push_back(Font("Courier","",12));
    _codes.push_back(13); _fonts.push_back(Font("Courier","Oblique",12));
    _codes.push_back(14); _fonts.push_back(Font("Courier","Bold",12));
    _codes.push_back(15); _fonts.push_back(Font("Courier","Bold Oblique",12));
    _codes.push_back(16); _fonts.push_back(Font("Helvetica","",12));
    _codes.push_back(17); _fonts.push_back(Font("Helvetica","Oblique",12));
    _codes.push_back(18); _fonts.push_back(Font("Helvetica","Bold",12));
    _codes.push_back(19); _fonts.push_back(Font("Helvetica","Bold Oblique",12));
    _codes.push_back(20); _fonts.push_back(Font("Helvetica","Narrow",12));
    _codes.push_back(21); _fonts.push_back(Font("Helvetica","Narrow Oblique",12));
    _codes.push_back(22); _fonts.push_back(Font("Helvetica","Narrow Bold",12));
    _codes.push_back(23); _fonts.push_back(Font("Helvetica","Narrow Bold Oblique",12));
    _codes.push_back(24); _fonts.push_back(Font("New Century Schoolbook","Roman",12));
    _codes.push_back(25); _fonts.push_back(Font("New Century Schoolbook","Italic",12));
    _codes.push_back(26); _fonts.push_back(Font("New Century Schoolbook","Bold",12));
    _codes.push_back(27); _fonts.push_back(Font("New Century Schoolbook","Bold Italic",12));
    _codes.push_back(28); _fonts.push_back(Font("Palatino","Roman",12));
    _codes.push_back(29); _fonts.push_back(Font("Palatino","Italic",12));
    _codes.push_back(30); _fonts.push_back(Font("Palatino","Bold",12));
    _codes.push_back(31); _fonts.push_back(Font("Palatino","Bold Italic",12));
    _codes.push_back(32); _fonts.push_back(Font("Symbol","",12));
    _codes.push_back(33); _fonts.push_back(Font("Zapf Chancery Medium","Italic",12));
    _codes.push_back(34); _fonts.push_back(Font("Zapf Dingbats","",12));
  }

  virtual ~XFigPostscriptFontManager() {}

public:
  int getCode(const Font & font)
  {
    for(unsigned int i = 0; i < _fonts.size(); i++)
    {
      if(_fonts[i].getFamily() == font.getFamily() && _fonts[i].getType() == font.getType())
      {
        return _codes[i];
      }
    }
    throw Exception("XFigPostcriptFontManager::getCode. Unknown font: " + font.toString());
  }

  const Font & getFont(int &code) const throw (Exception)
  {
    for(unsigned int i = 0; i < _codes.size(); i++)
    {
      if(_codes[i] == code)
      {
        return _fonts[i];
      }
    }
    throw Exception("XFigPostscriptFontManager::getColor. No font associated to this code: " + TextTools::toString(code));
  }
  vector<int> getCodes() const { return _codes; }
  vector<Font> getFonts() const { return _fonts; }
  unsigned int getNumberOfFonts() const { return _fonts.size(); }

};

} // end of namespace.

#endif //_FONTMANAGER_H_

