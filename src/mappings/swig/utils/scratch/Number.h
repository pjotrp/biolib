//
// File: Number.h
// Created by: Julien Dutheil
// Created on: Thu Nov 13 16:29:03 2003
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

#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "Clonable.h"

namespace bpp
{

/**
 * @brief The Number object template class.
 *
 * This template class may be used to deal with number in an object way.
 */
template<class T> class Number: public Clonable
{
	protected:
		/** @brief The value of this parameter. */
		T _value;
	
	public:
		
		/**
		 * @brief Build a new Number object with a specific value.
		 *
		 * @param value The value that the Number must have.
		 */
		Number(const T & value = 0): _value(value) {}
			
		virtual ~Number() {}

    Number<T> & operator=(const T & t)
    { 
      _value = t;
      return *this;
    }
	
	public:
	
		/**
		 * @name The Clonable interface.
		 *
		 * @{
		 */
		Number<T> * clone() const { return new Number<T>(_value); }
		/** @} */
	
	public:
		
		/**
		 * @brief Get the value of this number.
		 *
		 * @return The value of this number.
		 */
		T getValue() const { return _value; }
};

} //end of namespace bpp.

#endif	//_NUMBER_H_

