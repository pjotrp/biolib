//
// File: KeyvalTools.cpp
// Created by: Julien Dutheil
// Created on: Mon May 13:16 CET 2009
//

/*
Copyright or © or Copr. CNRS, (2009)

This software is a computer program whose purpose is to provide classes
for numerical calculus.

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

#include "KeyvalTools.h"

using namespace bpp;

void KeyvalTools::singleKeyval(const string& desc, string& key, string& val) throw (Exception)
{
  StringTokenizer st(desc, "=");
  if(st.numberOfRemainingTokens() != 2) throw Exception("NumCalcApplicationTools::keyval(). Bad syntax! keyval should be of the form 'key=value'.");
  key = st.nextToken();
  val = st.nextToken();
}

void KeyvalTools::multipleKeyvals(const string& desc, map<string,string>& keyvals) throw (Exception)
{
  StringTokenizer st(desc, ",");
  string key, val;
  while(st.hasMoreToken())
  {
    singleKeyval(st.nextToken(), key, val);
    keyvals[key] = val;
  }
}

void KeyvalTools::parseProcedure(const string& desc, string& name, map<string, string>& args) throw (KeyvalException)
{
  string::size_type begin = desc.find_first_of("(");
  if (begin == string::npos)
    throw KeyvalException("KeyvalTools::parseProcedure. Bad keyval procedure, missing opening parenthesis.");
  string::size_type end = desc.find_last_of(")");
  if (end == string::npos)
    throw KeyvalException("KeyvalTools::parseProcedure. Bad keyval procedure, missing closing parenthesis.");
  if(!TextTools::isEmpty(desc.substr(end + 1)))
    throw KeyvalException("KeyvalTools::parseProcedure. Bad keyval procedure, extra characters after closing parenthesis: " + desc.substr(end + 1));
  //Get the procedure name (without leading spaces):
  name = TextTools::removeFirstWhiteSpaces(desc.substr(0, begin));
  multipleKeyvals(desc.substr(begin + 1, end - begin - 1), args);
}

