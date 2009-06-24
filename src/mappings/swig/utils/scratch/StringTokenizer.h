//
// File: StringTokenizer.h
// Author : Julien Dutheil
//          Sylvain Gaillard
// Last modification : Monday September 20 2004
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

#ifndef _STRINGTOKENIZER_H_
#define _STRINGTOKENIZER_H_

#include <deque>
#include <string>

using namespace std;

#include "Exceptions.h"

namespace bpp
{

/**
 * @brief A tokenizer for strings.
 *
 * Splits a string according to a given (set of) delimiter(s).
 */
class StringTokenizer
{
	protected:

		/** @brief Where the tokens are stored. */
		deque<string> tokens;
		
		/** @brief the current position in the token list. */
		unsigned int currentPosition;

	public:
		
		/**
		 * @brief Build a new StringTokenizer from a string.
		 *
		 * @param s                The string to parse.
		 * @param delimiters       Chars that must be considered as delimiters.
		 * @param solid            If true, delimiters is considered as a single bloc delimiter.
     * @param allowEmptyTokens Tell if empty tokens are allowed or should be ignored.
		 */
		StringTokenizer(const string & s, const string & delimiters = " \t\n\f\r", bool solid = false, bool allowEmptyTokens = false);
		
		virtual ~StringTokenizer() {}
	
	public:
		
		/**
		 * @brief Get the next available token.
		 * If no token is availbale, throw an Exception.
		 *
		 * @return The next token if there is one.
		 */
		string nextToken() throw (Exception);
	
		/**
		 * @brief Tell if some token are still available.
		 * @return True if some token are still available.
		 */
		bool hasMoreToken() const { return currentPosition < tokens.size(); }
	
		/**
		 * @brief Tell how many tokens are available.
		 *
		 * @return the number of tokens available.
		 */
		int numberOfRemainingTokens() const { return tokens.size() - currentPosition; }

		/**
		 * @brief Get a particular token.
		 *
		 * Do not move the iterator.
		 *
		 * @param pos The index of the token.
		 * @return the token at position 'pos'.
		 */
		string getToken(unsigned int pos) const { return tokens[pos]; }

		/**
		 * @brief Retrieve all tokens.
		 *
		 * @return A reference toward the vector of tokens.
		 */
		const deque<string> & getTokens() const { return tokens; }

    /**
     * @brief remove all empty token from the current position.
     */
    void removeEmptyTokens();

};

} //end of namespace bpp.

#endif	//_STRINGTOKENIZER_H_

