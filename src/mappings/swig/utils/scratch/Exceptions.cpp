//
// File Exceptions.cpp
// Created by: Guillaume Deuchst
//              Julien Dutheil
//              Sylvain Gaillard
// Last modification : Thu Jul 22 2004
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

#include "Exceptions.h"
#include "TextTools.h"

using namespace bpp;

/******************************************************************************/
  
BadIntegerException::BadIntegerException(const char *   text, int badInt):
  Exception(string(text) + "(" + TextTools::toString(badInt) + ")"),
  _badInt(badInt) {}

BadIntegerException::BadIntegerException(const string & text, int badInt):
  Exception(text + "(" + TextTools::toString(badInt) + ")"),
  _badInt(badInt) {}

/******************************************************************************/

BadNumberException::BadNumberException(const char *   text, double badNumber):
  Exception(string(text) + "(" + TextTools::toString(badNumber) + ")"),
  _badNumber(badNumber) {}

BadNumberException::BadNumberException(const string & text, double badNumber):
  Exception(text + "(" + TextTools::toString(badNumber) + ")"),
  _badNumber(badNumber) {}

/******************************************************************************/

NumberFormatException::NumberFormatException(const char *   text, const string & badNumber):
  Exception(string(text) + "(" + badNumber + ")"),
  _badNumber(badNumber) {}

NumberFormatException::NumberFormatException(const string & text, const string & badNumber):
  Exception(text + "(" + badNumber + ")"),
  _badNumber(badNumber) {}

/******************************************************************************/
  
IndexOutOfBoundsException::IndexOutOfBoundsException(const char *   text, int badInt, int lowerBound, int upperBound):
  BadIntegerException(
    "out of [" + TextTools::toString(lowerBound) +  ", " + TextTools::toString(upperBound) + "])" + string(text),
    badInt),
  _lowerBound(lowerBound),
  _upperBound(upperBound) {}

IndexOutOfBoundsException::IndexOutOfBoundsException(const string & text, int badInt, int lowerBound, int upperBound):
  BadIntegerException("out of [" + TextTools::toString(lowerBound) + ", " + TextTools::toString(upperBound) +  "])" + text,
    badInt),
  _lowerBound(lowerBound),
  _upperBound(upperBound) {}

int * IndexOutOfBoundsException::getBounds() const
{
  int * bounds = new int[2];
  bounds[0] = _lowerBound;
  bounds[1] = _upperBound;
  return bounds;
}

/******************************************************************************/

