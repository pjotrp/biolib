//
// File: ColorSet.h
// Created by: Julien Dutheil
// Created on: Mon Apr 14 2008
//

/*
Copyright or © or Copr. CNRS, (November 17, 2008)

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

#ifndef _COLORSET_H_
#define _COLORSET_H_

#include "RGBColor.h"
#include "MapTools.h"

// From the STL:
#include <vector>
using namespace std;

namespace bpp
{

/**
 * @brief Specify a set of color definitions.
 */
class ColorSet
{
  public:
    ColorSet() {}
    virtual ~ColorSet() {}

  public:

    /**
     * @brief Get the color object corresponding to a given name.
     *
     * @param name The name of the color to look for.
     * @return The color associated to the given name.
     * @throw Exception if the name is not assigned to any color.
     */
    virtual const RGBColor& getColor(const string & name) const throw (Exception) = 0;

    /**
     * @brief Get the ith color object in the set.
     *
     * @param index The index of the color to look for.
     * @return The color associated to the given index.
     * @throw IndexOutOfBoundsException if the index is not assigned to any color.
     */
    virtual const RGBColor& getColor(unsigned int index) const throw (IndexOutOfBoundsException) = 0;

    /**
     * @return All valid color names.
     */
    virtual vector<string> getColorNames() const = 0;
  
    /**
     * @return The total number of colors available.
     */
    virtual unsigned int getNumberOfColors() const = 0;
};


/**
 * @brief Partial implementation of the ColorSet interface.
 *
 * Derivative classes just have to fill the _colors map in the constructor of the class.
 */
class AbstractColorSet:
  public ColorSet
{
  protected:
    map<string, RGBColor> _colors;

  public:
    const RGBColor& getColor(const string & name) const throw (Exception)
    {
      map<string, RGBColor>::const_iterator it = _colors.find(name);
      if(it != _colors.end()) return it->second;
      else throw Exception("AbstractColorSet::getColor(name): no color with name " + name);
    }

    const RGBColor& getColor(unsigned int index) const throw (IndexOutOfBoundsException)
    {
      if(index >= _colors.size()) throw IndexOutOfBoundsException("AbstractColorSet::getColor(index): invalid index.", index, 0, _colors.size() - 1);
      map<string, RGBColor>::const_iterator it = _colors.begin();
      for(unsigned int i = 0; i < index; i++) it++;
      return it->second;
    }
    
    vector<string> getColorNames() const { return MapTools::getKeys(_colors); }
    
    unsigned int getNumberOfColors() const { return _colors.size(); }
};

} // end of namespace bpp;

#endif //_COLORSET_H_

