

//
// File: Font.h
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

#ifndef _FONT_H_
#define _FONT_H_

#include "Clonable.h"

namespace bpp
{

/**
 * @brief Data structure for fonts.
 */
class Font:
  public virtual Clonable
{
  protected:
    string _family;
    string _series;
    string _type;
    unsigned int _size;

  public:
    Font(const string & family, const string & type, unsigned int size):
      _family(family), _series(), _type(type), _size(size) {}

    Font(const string & family = "default", const string & series = "default", const string & type = "", unsigned int size = 12):
      _family(family), _series(series), _type(type), _size(size) {}

    virtual ~Font() {}

#ifdef NO_VIRTUAL_COV
    Clonable *
#else
    Font *
#endif
    clone() const { return new Font(*this); }
    

  public:
    bool operator==(const Font & font)
    {
      return _family == font._family && _type == font._type && _size == font._size;
    }

    /**
     * @return The family component of this font.
     */
    const string & getFamily() const { return _family; }

    /**
     * @return The series component of this font.
     */
    const string & getSeries() const { return _series; }

    /**
     * @return The type component of this font.
     */
    const string & getType() const { return _type; }

    /**
     * @return The size component of this font.
     */
    const unsigned int & getSize() const { return _size; }

    /**
     * @param family The family component of this font.
     */
    void setFamily(const string & family) { _family = family; }

    /**
     * @param series The series component of this font.
     */
    void setSeries(const string & series) { _series = series; }

    /**
     * @param type The type component of this font.
     */
    void setType(const string & type) { _type = type; }

    /**
     * @param size The size component of this font.
     */
    void setSize(unsigned int size) { _size = size; }

    /**
     * @return A text description of this font (family type size).
     */
    string toString() const { return _family + "/" + _series + "/" + _type + "/" + TextTools::toString(_size); }

};

} // end of namespace bpp.

#endif //_FONT_H_


