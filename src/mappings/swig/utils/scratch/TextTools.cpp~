//
// File: TextTools.cpp
// Created by: Julien Dutheil
// Created on: Fri Aug  8 12:57:50 2003
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

#include "TextTools.h"

using namespace bpp;

#include <ctype.h>
#include <sstream>
#include <iomanip>

using namespace std;

/******************************************************************************/

bool TextTools::isEmpty(const string & s)
{
  for(unsigned int i = 0; i < s.size(); i++)
  {
    char c = s[i];
    if(c != ' ' && c != '\n' && c != '\t') return false;
  }
  return true;
}

/******************************************************************************/

string TextTools::toUpper(const string & s)
{
  string result = "";
  for(unsigned int i = 0; i < s.size(); i++)
  {
    result += toupper(s[i]);
  }
  return result;
}

/******************************************************************************/

string TextTools::toLower(const string & s)
{
  string result = "";
  for(unsigned int i = 0; i < s.size(); i++)
  {
    result += tolower(s[i]);
  }
  return result;
}

/******************************************************************************/

bool TextTools::isWhiteSpaceCharacter(char c)
{
    return (c == ' ')
        || (c == '\t')
        || (c == '\n')
        || (c == '\r')
        || (c == '\f');  
}

/******************************************************************************/

string TextTools::removeWhiteSpaces(const string & s)
{
  // Copy sequence
  string st (s);
  
  // For all sequence's characters
  for (unsigned int i = 0; i < st.size(); i++)
  {
    if(isWhiteSpaceCharacter(st[i]))
    {
      st.erase(st.begin() + i); // Remove character
      i--;
    }
  }

  // Send result
  return st;
}

/******************************************************************************/

string TextTools::removeFirstWhiteSpaces(const string & s)
{
  // Copy sequence
  string st (s);
  
  while(st.size() > 0 && isWhiteSpaceCharacter(st[0]))
  {
    st.erase(st.begin());
  }

  // Send result
  return st;
}

/******************************************************************************/

string TextTools::removeLastWhiteSpaces(const string & s)
{
  // Copy sequence
  string st (s);
  
  while(st.size() > 0 && isWhiteSpaceCharacter(st[st.size() - 1]))
  { 
    st.erase(st.end() - 1);
  }

  // Send result
  return st;
}

/******************************************************************************/

string TextTools::removeSurroundingWhiteSpaces(const string & s)
{
  return removeFirstWhiteSpaces(removeLastWhiteSpaces(s));
}

/******************************************************************************/

bool TextTools::isNewLineCharacter(char c)
{
  return (c == '\n')
      || (c == '\r');
}

/******************************************************************************/

string  TextTools::removeNewLines(const string & s)
{
  // Copy string
  string st (s);

  // For all string's characters
  for (unsigned int i = 0; i < st.size(); i++)
  {
    if (isNewLineCharacter(st[i]))
    {
      st.erase(st.begin() + i); // Remove character
      i--;
    }
  }

  // Send result
  return st;
}

/******************************************************************************/

string TextTools::removeLastNewLines(const string & s)
{
  // Copy string
  string st (s);

  while (st.size() > 0 && isNewLineCharacter(st[st.size() - 1]))
  {
    st.erase(st.end() - 1);
  }

  // Send result
  return st;
}

/******************************************************************************/

bool TextTools::isDecimalNumber(char c)
{
  if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' 
  || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') return true;
  else return false;
}

/******************************************************************************/

bool TextTools::isDecimalNumber(const string & s, char dec)
{
  unsigned int sepCount = 0;
  for(unsigned int i = 0; i < s.size(); i++)
  {
    char c = s[i];
    if(c == dec) sepCount++;
    else if(!isDecimalNumber(c)) return false;
    if(sepCount > 1) return false;
  }
  return true;
}

/******************************************************************************/

string TextTools::toString(int i)
{
  ostringstream oss;
  oss << i;
  return oss.str();
}

/******************************************************************************/

string TextTools::toString(char c)
{
  ostringstream oss;
  oss << c;
  return oss.str();
}

/******************************************************************************/

string TextTools::toString(double d, int precision)
{
  ostringstream oss;
  oss << setprecision(precision) << d;
  return oss.str();
}

/******************************************************************************/

int TextTools::toInt(const string & s)
{
  istringstream iss(s);
  int i;
  iss >> i;
  return i;
}

/******************************************************************************/

double TextTools::toDouble(const string & s) 
{
  istringstream iss(s);
  double d;
  iss >> d;
  return d;
}

/******************************************************************************/

string TextTools::resizeRight(const string & s, unsigned int newSize, char fill) 
{
  if(s.size() > newSize) return s.substr(0, newSize);
  else return s + string(newSize - s.size(), fill);
}

/******************************************************************************/

string TextTools::resizeLeft(const string & s, unsigned int newSize, char fill)
{
  if(s.size() > newSize) return s.substr(s.size() - newSize);
  else return string(newSize - s.size(), fill) + s;
}

/******************************************************************************/

vector<string> TextTools::split(const string & s, unsigned int n)
{
  vector<string> v;
  string tmp = s;
  while(tmp.size() > n)
  {
    v.push_back(tmp.substr(0, n));
    tmp = tmp.substr(n);
  }
  v.push_back(tmp);
  return v;
}

/******************************************************************************/

string TextTools::removeSubstrings(const string & s, char blockBeginning, char blockEnding)
throw (Exception)
{
  string t = "";
  int blockCount = 0;
  int begPos = 0;
  for(unsigned int i = 0; i < s.size(); i++)
  {
    char current = s[i];
    if(current == blockBeginning)
    {
      blockCount++;
      t += s.substr(begPos, i);
    }
    else if(current == blockEnding)
    {
      blockCount--;
      if(blockCount == 0) {
        begPos = i + 1;
      }
      else if(blockCount < 0)
        throw Exception("TextTools::removeSubstrings(). " +
          string("Ending block character without corresponding beginning one at position ") + toString((int)i) + ".");
    }
  }
  t += s.substr(begPos, s.npos);
  return t;
}

/******************************************************************************/

string TextTools::removeChar(const string & s, char c)
{
  // Copy sequence
  string st(s);

  // For all sequence's characters
  for (unsigned int i = 0; i < st.size(); i++)
  {
    if (st[i] == c)
    {
      st.erase(st.begin() + i); // Remove character
      i--;
    }
  }

  // Send result
  return st;
}

/******************************************************************************/

unsigned int TextTools::count(const string& s, const string& pattern)
{
  unsigned int count = 0;
  string::size_type index = s.find(pattern);
  while(index != string::npos)
  {
    count++;
    index = s.find(pattern, index+1);
  }
  return count;
}

/******************************************************************************/

bool TextTools::startsWith(const string& s, const string& pattern)
{
  if(s.size() < pattern.size()) return false;
  return (s.substr(0, pattern.size()) == pattern);
}

/******************************************************************************/

bool TextTools::endsWith(const string& s, const string& pattern)
{
  if(s.size() < pattern.size()) return false;
  return (s.substr(s.size() - pattern.size()) == pattern);
}

/******************************************************************************/

