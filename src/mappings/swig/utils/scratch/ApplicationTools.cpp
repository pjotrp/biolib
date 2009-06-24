//
// File: ApplicationTools.cpp
// Created by: Julien Dutheil
// Created on: Fri Oct 21 16:19 2005
// From old file created on: Sun Dec 14 09:36:26 2003
//

/*
Copyright or © or Copr. CNRS, (November 16, 2004)

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

#include "ApplicationTools.h"

using namespace bpp;

// From the STL:
#include <cmath>

using namespace std;

/******************************************************************************/

ostream * ApplicationTools::error   = &cerr;
ostream * ApplicationTools::message = &cout;
ostream * ApplicationTools::warning = &cout;
time_t    ApplicationTools::startTime;
unsigned int ApplicationTools::terminalWidth = 80;
float ApplicationTools::terminalSplit = 0.5;

/******************************************************************************/

bool ApplicationTools::parameterExists(
  const string & parameterName,
  map<string, string> & params)
{
  return params.find(parameterName) != params.end() && !TextTools::isEmpty(params[parameterName]);
}
  
/******************************************************************************/

string ApplicationTools::getAFilePath(
  const string & parameter,
  map<string, string> & params,
  bool isRequired,
  bool mustExist,
  const string & suffix,
  bool suffixIsOptional) throw (Exception)
{
  string filePath = getStringParameter(parameter, params, "none", suffix, suffixIsOptional, false);
  if(filePath == "") filePath = "none";
  if(filePath == "none" && isRequired)
  {
    throw Exception("You must specify a file for this parameter: " + parameter);
  }
  if(filePath == "none") return filePath;
  if(mustExist && !FileTools::fileExists(filePath))
  {
    throw Exception("File does not exists: " + filePath);
  }
  return filePath;
}

/******************************************************************************/

double ApplicationTools::getDoubleParameter(
  const string & parameterName,
  map<string, string> & params,
  double defaultValue,
  const string & suffix,
  bool suffixIsOptional,
  bool warn)
{
  double dParam = defaultValue;
  if(parameterExists(parameterName + suffix, params))
  {
    dParam = TextTools::toDouble(params[parameterName + suffix]);
  }
  else if(suffixIsOptional && parameterExists(parameterName, params))
  {
    dParam = TextTools::toDouble(params[parameterName]);
  }
  else if(warn)
  {
    displayWarning("Parameter " + parameterName + suffix + " not specified. Default used instead: " + TextTools::toString(defaultValue));
  }
  return dParam;
}

/******************************************************************************/

int ApplicationTools::getIntParameter(
  const string & parameterName,
  map<string, string> & params,
  int defaultValue,
  const string & suffix,
  bool suffixIsOptional,
  bool warn)
{
  int iParam = defaultValue;
  if(parameterExists(parameterName + suffix, params)) {
    iParam = TextTools::toInt(params[parameterName + suffix]);
  } else if(suffixIsOptional && parameterExists(parameterName, params)) {
    iParam = TextTools::toInt(params[parameterName]);
  } else if(warn) {
    displayWarning("Parameter " + parameterName + suffix + " not specified. Default used instead: " + TextTools::toString(defaultValue));
  }
  return iParam;
}

/******************************************************************************/

string ApplicationTools::getStringParameter(
  const string & parameterName,
  map<string, string> & params,
  const string & defaultValue,
  const string & suffix,
  bool suffixIsOptional,
  bool warn)
{
  string sParam = defaultValue;
  if(parameterExists(parameterName + suffix, params)) {
    sParam = params[parameterName + suffix];
  } else if(suffixIsOptional && parameterExists(parameterName, params)) {
    sParam = params[parameterName];
  } else if(warn) {
    displayWarning("Parameter " + parameterName + " not specified. Default used instead: " + defaultValue);
  }
  return sParam;
}

/******************************************************************************/

bool ApplicationTools::getBooleanParameter(
  const string & parameterName,
  map<string, string> & params,
  bool defaultValue,
  const string & suffix,
  bool suffixIsOptional,
  bool warn)
{
  bool bParam = defaultValue;
  if(parameterExists(parameterName + suffix, params))
  {
    string sParam = params[parameterName + suffix];
    bParam = (sParam == "true") 
        || (sParam == "TRUE")
        || (sParam == "t")
        || (sParam == "T")
        || (sParam == "yes")
        || (sParam == "YES")
        || (sParam == "y")
        || (sParam == "Y")
        || (sParam == "1");
  }
  else if(suffixIsOptional && parameterExists(parameterName, params)) {
    string sParam = params[parameterName];
    bParam = (sParam == "true") 
        || (sParam == "TRUE")
        || (sParam == "t")
        || (sParam == "T")
        || (sParam == "yes")
        || (sParam == "YES")
        || (sParam == "y")
        || (sParam == "Y")
          || (sParam == "1");
  }
  else if(warn)
  {
    displayWarning("Parameter " + parameterName + " not specified. Default used instead: " + TextTools::toString(defaultValue));
  }
  return bParam;
}

/******************************************************************************/

void ApplicationTools::displayMessage(const string & text) { if(message) *message << text << endl; }
    
void ApplicationTools::displayError(const string & text) { if(error) *error << "ERROR!!! " << text << endl; }
    
void ApplicationTools::displayWarning(const string & text) { if(warning) *warning << "WARNING!!! " << text << endl; }

void ApplicationTools::displayTask(const string & text, bool eof)
{
  if(message)
  {
    *message << TextTools::resizeRight(text, (unsigned int) (terminalWidth * terminalSplit - 1), '.') << ": ";
    if(eof) *message << endl;
    else    message->flush();
  }
}
    
void ApplicationTools::displayTaskDone() { if(message) *message << "Done." << endl; }

/******************************************************************************/

void ApplicationTools::displayGauge(unsigned int iter, unsigned int total, char symbol, string mes)
{
  if(!message) return;
  unsigned int width = (unsigned int) (terminalWidth * terminalSplit - 2);
  string gauge = string((unsigned int) width * iter / total, symbol);
  string fill = string(width - gauge.length(), ' ');
  gauge = "[" + gauge + fill + "] " + TextTools::resizeLeft(TextTools::toString(100 * iter / total), 3) + "%";
  if (mes.size() > 80 - gauge.size())
    mes = TextTools::resizeRight(mes, 80 - gauge.size());
  *message << '\r' + mes + gauge;
  message->flush();
}

/******************************************************************************/
  
void ApplicationTools::displayTime(const string & msg)
{
  time_t endTime;
  time(&endTime);
  double nsec = difftime(endTime, startTime);
  double nmin = floor(nsec/60.);
  double nhou = floor(nmin/60.);
  double nday = floor(nhou/24.);
  nhou = nhou - nday * 24;
  nmin = nmin - (nday * 24 + nhou) * 60;
  nsec = nsec - ((nday * 24 + nhou) * 60 + nmin) * 60;
  *message << msg << " ";
  *message << nday << "d, ";
  *message << nhou << "h, ";
  *message << nmin << "m, ";
  *message << nsec << "s." << endl;
}

/******************************************************************************/
  
double ApplicationTools::getTime()
{
  time_t endTime;
  time(&endTime);
  return difftime(endTime, startTime);
}

/******************************************************************************/

