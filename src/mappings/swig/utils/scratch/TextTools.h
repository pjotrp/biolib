//
// File: TextTools.h
// Created by: Julien Dutheil
// Created on: Fri Aug  8 12:57:50 2003
//

/*
   Copyright or © or Copr. CNRS, (November 17, 2004)

   This software is a computer program whose purpose is to provide basal and
   utilitary classes. This file belongs to the Bio++ Project.

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

#ifndef _TEXTTOOLS_H_
#define _TEXTTOOLS_H_

#include "Exceptions.h"


// From the STL:
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

namespace bpp
{

  /**
   * @brief Some utilitary functions that work on strings.
   */
  class TextTools
  {
    public:

      /**
       * @brief Tell if a string is empty.
       *
       * A string is considered to be 'empty' if it is only made of white spaces.
       *
       * @param s The string to check.
       * @return True if the string has only white characters.
       */
      static bool isEmpty(const string & s);

      /**
       * @brief Make the string uppercase.
       *
       * @param s The string to analyse.
       * @return A copy of the string with all chars uppercase.
       */
      static string toUpper(const string & s);

      /**
       * @brief Make the string lowercase.
       *
       * @param s The string to analyse.
       * @return A copy of the string with all chars lowercase.
       */
      static string toLower(const string & s);

      /**
       * @brief Tell if a character is a white space or not.
       *
       * @param c The character to check.
       * @return True if c is one of the following: ' ', '\\t', '\\n', '\\r' or '\\f'.
       */
      static bool isWhiteSpaceCharacter(char c);

      /**
       * @brief Remove all white spaces characters in a string.
       *
       * @param s The string to parse.
       * @return A copy of 's' without white spaces characters.
       */
      static string removeWhiteSpaces (const string & s);

      /**
       * @brief Remove all white spaces characters at the beginning of a string.
       *
       * @param s The string to parse.
       * @return A copy of 's' beginning with the first non-white character.
       */
      static string removeFirstWhiteSpaces (const string & s);

      /**
       * @brief Remove all white spaces characters at the end of a string.
       *
       * @param s The string to parse.
       * @return A copy of 's' ending with the last non-white character.
       */
      static string removeLastWhiteSpaces (const string & s);

      /**
       * @brief Remove all white spaces characters at the beginning and the
       * end of a string.
       *
       * @param s The string to parse.
       * @return A copy of 's' beginning with the first non-white character
       * and ending with the last one.
       */
      static string removeSurroundingWhiteSpaces(const string & s);

      /**
       * @brief Tell if a character is a new line character or not.
       *
       * @param c The character to check.
       * @return True if c is one of the following: '\\n' or '\\r'.
       */
      static bool isNewLineCharacter(char c);

      /**
       * @brief Remove all new line characters in a string.
       *
       * @param s The string to parse.
       * @return A copy of 's' without new line characters.
       */
      static string removeNewLines (const string & s);

      /**
       * @brief Remove all new line characters at the end of a string.
       *
       * @param s The string to parse.
       * @return A copy of 's' ending with the last non-new line character.
       */
      static string removeLastNewLines(const string & s);

      /**
       * @brief Tell is a given character describes a decimal number.
       *
       * @param c The character to check.
       * @return true if the given character is the reprensentation of a decimal number.
       */
      static bool isDecimalNumber(char c);

      /**
       * @brief Tell is a given character string describes a decimal number.
       *
       * NB: for now, this parser will not recognize thosands delimiters, and not the scientific notation neither.
       * @param s The string to parse.
       * @param dec The decimal separator.
       * @return true if the given string is the representation of a decimal number.
       */
      static bool isDecimalNumber(const string & s, char dec = '.');

      /**
       * @brief General template method to convert to a string.
       *
       * @param t The object to convert.
       * @return A string equal to t.
       */
      template<class T> static string toString(T t)
      {
        ostringstream oss;
        oss << t;
        return oss.str();
      }

      /**
       * @brief Template string conversion.
       * 
       * @param t The object to convert.
       * @param precision To use (for numbers).
       * @return A string equal to t.
       */
      template<class T>
        static string toString(T t, int precision)
        {
          ostringstream oss;
          oss << setprecision(precision) << t;
          return oss.str();
        }

      /**
       * @brief General template method to convert from string.
       *
       * @param s The string to convert.
       * @return An object from string t.
       */
      template<class T> static T fromString(const string & s)
      {
        istringstream iss(s);
        T obj;
        iss >> obj;
        return obj;
      }

      /**
       * @brief Convert from int to string.
       *
       * @param i The integer to convert.
       * @return A string equal to i.
       */
      static string toString(int i);

      /**
       * @brief Convert from char to string.
       *
       * @param c The character to convert.
       * @return A string equal to c.
       */
      static string toString(char c);

      /**
       * @brief Convert from double to string.
       *
       * @param d The double to convert.
       * @param precision To use (for numbers).
       * @return A string equal to d.
       */
      static string toString(double d, int precision = 6);

      /**
       * @brief Convert from string to int.
       *
       * @param s The string to parse.
       * @return The integer corresponding to s.
       */
      static int toInt(const string & s);

      /**
       * @brief Convert from string to double.
       *
       * @param s The string to parse.
       * @return The double corresponding to s.
       */
      static double toDouble(const string & s);

      /**
       * @brief Template to string conversion.
       * 
       * @param s The string to parse.
       * @return An object of class R corresponding to s.
       */
      template<class T>
        static T to(const string & s)
        {
          istringstream iss(s);
          T t;
          iss >> t;
          return t;
        }

      /**
       * @brief Send a string of size 'newSize', which is a copy of 's' truncated or
       * filled with character 'fill' at the end.
       *
       * @param s       The string to parse.
       * @param newSize The new string size.
       * @param fill    The character to use to fill the string id length < newSize.
       * @return A string of size newsize which is a copy from the left of s.
       */
      static string resizeRight(const string & s, unsigned int newSize, char fill = ' ');

      /**
       * @brief Send a string of size 'newSize', which is a copy of 's' truncated or
       * filled with character 'fill' at the beginning.
       *
       * @param s       The string to parse.
       * @param newSize The new string size.
       * @param fill    The character to use to fill the string id length < newSize.
       * @return A string of size newsize which is a copy from the right of s.
       */
      static string resizeLeft(const string & s, unsigned int newSize, char fill = ' ');

      /**
       * @brief Split a string into parts of size 'n'.
       *
       * The last part may contain < n chars.
       *
       * @param s The string to parse.
       * @param n The number of tokens.
       * @return A vector of strings with all tokens.
       */
      static vector<string> split(const string & s, unsigned int n);

      /**
       * @brief Remove substrings from a string.
       *
       * All substrings beginning with blockBeginning
       * and ending with blockEnding will be removed.
       * Nesting blocks are allowed, the most extern block will be removed.
       *
       * @param s The string to parse.
       * @param blockBeginning The character specifying the beginning of each block.
       * @param blockEnding    The character specifying the end of each block.
       * @return The string with all blocks removed.
       * @throw Exception If some blocks are not well formed.
       */
      static string removeSubstrings(const string & s, char blockBeginning, char blockEnding)
        throw (Exception);

      /**
       * @brief Remove all occurences of a character in a string.
       *
       * @param s The string to parse.
       * @param c The character to remove.
       * @return The string with all specified chars removed.
       */
      static string removeChar(const string & s, char c);

      /**
       * @brief Count the occurences of a given pattern in a string.
       *
       * @param s The string to search.
       * @param pattern The pattern to use (this is a mere string, not a regexp!).
       * @return The number of occurences of 'pattern' in 's'.
       */
      static unsigned int count(const string& s, const string& pattern);

      /**
       * @brief Tell is a string begins with a certain motif.
       *
       * @param s The string to search.
       * @param pattern The pattern to use (this is a mere string, not a regexp!).
       * @return true/false
       */
      static bool startsWith(const string& s, const string& pattern);

      /**
       * @brief Tell is a string ends with a certain motif.
       *
       * @param s The string to search.
       * @param pattern The pattern to use (this is a mere string, not a regexp!).
       * @return true/false
       */
      static bool endsWith(const string& s, const string& pattern);
  };

} //end of namespace bpp.

#endif	//_TEXTTOOLS_H_

