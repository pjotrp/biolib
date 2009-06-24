//
// File FileTools.cpp
// Author : Guillaume Deuchst
//          Julien Dutheil
// Last modification : Tuesday August 23 2005
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

#include "FileTools.h" // class's header file
#include "TextTools.h"
#include <sys/stat.h>

using namespace bpp;

/******************************************************************************/

char FileTools::DIR_SEP = '/';

/******************************************************************************/

bool FileTools::fileExists(const string & filename)
{
  ifstream file(filename.c_str());
  bool test = file;
  file.close();
  return test;
}

/******************************************************************************/

bool FileTools::directoryExists(const string & path)
{
  ifstream file(path.c_str());
  bool test = file;
  file.close();
  return test;
}

/******************************************************************************/

string FileTools::getFileName(const string & path, char dirSep)
{
  int end = path.find_last_of(".");
  int begin = path.find_last_of(dirSep) + 1;

  // Return an empty string if specified string isn't a path
  if (begin > end) return "";

  // Copy path and deletion of directories and extension
  string result(path);
  result.erase(result.begin() + end, result.end());
  result.erase(result.begin(), result.begin() + begin);

  // Send file name
  return result;
}

/******************************************************************************/

string FileTools::getParent(const string & path, char dirSep)
{
  // Position of file name:
  int begin = path.find_last_of(dirSep);

  // Copy string and delte filename:
  string result(path);
  result.erase(result.begin() + begin, result.end());

  // Send directories
  return result;
}

/******************************************************************************/

string FileTools::getExtension(const string & path)
{
  int end = path.find_last_of(".");
  return path.substr(end+1);
}

/******************************************************************************/

vector<string> FileTools::putStreamIntoVectorOfStrings(istream & input)
{
  vector<string> vs;
  string s = "";
  while(input)
  {
    getline(input, s, '\n');
    vs.push_back(s);
  }
  return vs;
}

/******************************************************************************/

string FileTools::getNextLine(istream & in)
{
  if(in.eof()) return string("");
  string temp("");
  while(!in.eof() && TextTools::isEmpty(temp)) {
    getline(in, temp, '\n');
  }
  return temp;
}

/******************************************************************************/

