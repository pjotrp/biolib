//
// File: StringTokenizer.cpp
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

#include "StringTokenizer.h"

using namespace bpp;

StringTokenizer::StringTokenizer(const string & s, const string & delimiters, bool solid, bool allowEmptyTokens)
{
	tokens = deque<string>();
	if (!solid)
  {
    string::size_type index = s.find_first_not_of(delimiters, 0);
		while(index != s.npos)
    {
      string::size_type newIndex = s.find_first_of(delimiters, index);
			if(newIndex != s.npos)
      {
				tokens.push_back(string(s.begin() + index, s.begin() + newIndex));
				if(!allowEmptyTokens) index = s.find_first_not_of(delimiters, newIndex);
        else                  index = newIndex + 1;
			}
      else
      {
				tokens.push_back(string(s.begin() + index, s.end()));
				index = newIndex;
			}
		}
	}
	else
  {
    string::size_type index = 0;
		while(index != s.npos)
    {
      string::size_type newIndex = s.find(delimiters, index);
			if(newIndex != s.npos)
      {
				tokens.push_back(string(s.begin() + index, s.begin() + newIndex));
				if(!allowEmptyTokens)
        {
          index = newIndex + delimiters.size();
          while(index != string::npos && s.substr(index, delimiters.size()) == delimiters) index++;
        }
        else index = newIndex + delimiters.size();
			}
      else
      {
				tokens.push_back(string(s.begin() + index, s.end()));
				index = newIndex;
			}
		}
	}
	currentPosition = 0;
}

string StringTokenizer::nextToken() throw (Exception)
{
	if(!hasMoreToken()) throw Exception("No more token in tokenizer.");
	return tokens[currentPosition++];
}

void StringTokenizer::removeEmptyTokens()
{
  for(unsigned int i = tokens.size(); i > currentPosition; i--)
  {
    if(tokens[i-1] == "") tokens.erase(tokens.begin() + i - 1);
  }
}

