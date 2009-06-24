//
// File: ApplicationTools.h
// Created by: Julien Dutheil
// Created on: Fri Oct 21 16:19 2005
// From old file created on: Sun Dec 14 09:36:26 2003
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

#ifndef _APPLICATIONTOOLS_H_
#define _APPLICATIONTOOLS_H_

#include "TextTools.h"
#include "FileTools.h"
#include "StringTokenizer.h"

// From the STL:
#include <map>
#include <vector>
#include <iostream>
#include <ctime>
using namespace std;

namespace bpp
{

/**
 * @brief This class provides some common tools for developping applications.
 *
 * These functions are designed for helping to parse an option file.
 * 
 * The option files are supposed to follow this simple format:<br>
 * @code
 * parameterName = parameterContent
 * @endcode
 * with one parameter per line.
 *
 * In files, shell comments:
 * @code
 * # my comment line here
 * @endcode,
 * C comments:
 * @code
 * / * my comment block here * /
 * @endcode
 * and C++ comments:
 * @code
 * // my comment line here
 * @endcode
 * are allowed, and ignored while parsing.
 *
 * Some methods for displaying information (messages, errors, warnings...) are also provided.
 *
 * Methods dealing with parameters takes as argument a map<string, string> object
 * containing the parameters (names are the keys of the map, and values are... the values of the map!).
 * These map objects may be obtained from the AttributesTools utilitary class.
 */
class ApplicationTools
{
  public:
    
    /**
     * @brief The output stream where errors have to be displayed.
     */
    static ostream * error;
    /**
     * @brief The output stream where messages have to be displayed.
     */
    static ostream * message;
    /**
     * @brief The output stream where warnings have to be displayed.
     */
    static ostream * warning;

    /**
     * @brief Timer variable.
     */
    static time_t startTime;

    /**
     * @brief The width of the output terminal (in character).
     */
    static unsigned int terminalWidth;

    /**
     * @brief The fraction of terminal width dedicated to messages.
     */
    static float terminalSplit;
  
  public:
    ApplicationTools();
    virtual ~ApplicationTools();
  
  public:

    /**
     * @brief Tells if a parameter have been specified.
     *
     * @param parameterName The name of the parameter.
     * @param params        The parameter list.
     * @return True is the parameter of specified name is in the list.
     */
    static bool parameterExists(const string & parameterName, map<string, string> & params);
  
    /**
     * @brief Get a double parameter.
     *
     * @param parameterName    The name of the corresponding parameter.
     * @param params           The attribute map where options may be found.
     * @param defaultValue     The default value to use if the parameter is not found.
     * @param suffix           A suffix to be applied to the parameter name.
     * @param suffixIsOptional Tell if the suffix is absolutely required.
     * @param warn             Tell if a warning must be sent in case the parameter is not found.
     * @return The corresponding value.
     */
    static double getDoubleParameter(
      const string & parameterName,
      map<string, string> & params,
      double defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true);
  
    /**
     * @brief Get an integer parameter.
     *
     * @param parameterName    The name of the corresponding parameter.
     * @param params           The attribute map where options may be found.
     * @param defaultValue     The default value to use if the parameter is not found.
     * @param suffix           A suffix to be applied to the parameter name.
     * @param suffixIsOptional Tell if the suffix is absolutely required.
     * @param warn             Tell if a warning must be sent in case the parameter is not found.
     * @return The corresponding value.
     */
    static int getIntParameter(
      const string & parameterName,
      map<string, string> & params,
      int defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true);
  
    /**
     * @brief Get a string parameter.
     *
     * @param parameterName    The name of the corresponding parameter.
     * @param params           The attribute map where options may be found.
     * @param defaultValue     The default value to use if the parameter is not found.
     * @param suffix           A suffix to be applied to the parameter name.
     * @param suffixIsOptional Tell if the suffix is absolutely required.
     * @param warn             Tell if a warning must be sent in case the parameter is not found.
     * @return The corresponding value.
     */
    static string getStringParameter(
      const string & parameterName,
      map<string, string> & params,
      const string & defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true);

    /**
     * @brief Get a boolean parameter.
     *
     * @param parameterName    The name of the corresponding parameter.
     * @param params           The attribute map where options may be found.
     * @param defaultValue     The default value to use if the parameter is not found.
     * @param suffix           A suffix to be applied to the parameter name.
     * @param suffixIsOptional Tell if the suffix is absolutely required.
     * @param warn             Tell if a warning must be sent in case the parameter is not found.
     * @return The corresponding value.
     */
    static bool getBooleanParameter(
      const string & parameterName,
      map<string, string> & params,
      bool defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true);

    /**
     * @brief Get a parameter.
     *
     * @param parameterName    The name of the corresponding parameter.
     * @param params           The attribute map where options may be found.
     * @param defaultValue     The default value to use if the parameter is not found.
     * @param suffix           A suffix to be applied to the parameter name.
     * @param suffixIsOptional Tell if the suffix is absolutely required.
     * @param warn             Tell if a warning must be sent in case the parameter is not found.
     * @return The corresponding value.
     */
    template<class T> static T getParameter(
      const string & parameterName,
      map<string, string> & params,
      T defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true)
    {
      T tParam = defaultValue;
      if(parameterExists(parameterName + suffix, params))
      {
        tParam = TextTools::to<T>(params[parameterName + suffix]);
      }
      else if(suffixIsOptional && parameterExists(parameterName, params))
      {
        tParam = TextTools::to<T>(params[parameterName]);
      } else if(warn)
      {
        displayWarning("Parameter " + parameterName + suffix + " not specified. Default used instead: " + TextTools::toString(defaultValue));
      }
      return tParam;
    }
  

    /**
     * @brief Get a file path.
     *
     * @param parameter        The name of the corresponding parameter.
     * @param params           The attribute map where options may be found.
     * @param isRequired       Tell if this path is strictly required or is optional
     * (in the first case, if the parameter is not found, the programm will
     * send an error and exit).
     * @param mustExist        Tell if the corresponding file must already exist.
     * @param suffix           A suffix to be applied to the parameter name.
     * @param suffixIsOptional Tell if the suffix is absolutely required.
     * @throw Exception        If no file path is specified and isRequired is
     *                         true, or the file does not exist and mustExist
     *                         is set to true.
     */
    static string getAFilePath(
      const string & parameter,
      map<string, string> & params,
      bool isRequired = true,
      bool mustExist = true,
      const string & suffix = "",
      bool suffixIsOptional = false) throw (Exception);

    /**
     * @brief Get a vector.
     *
     * @param parameterName    The name of the corresponding parameter.
     * @param params           The attribute map where options may be found.
     * @param separator        The character used to delimit values.
     * @param defaultValue     The default value to use if the parameter is not found.
     * @param suffix           A suffix to be applied to the parameter name.
     * @param suffixIsOptional Tell if the suffix is absolutely required.
     * @param warn             Tell if a warning must be sent in case the parameter is not found.
     * @return The corresponding value.
     */
    template<class T> static vector<T> getVectorParameter(
      const string & parameterName,
      map<string, string> & params,
      char separator,
      const string & defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true)
    {
      string s = getStringParameter(parameterName, params, defaultValue, suffix, suffixIsOptional, warn);
      StringTokenizer st(s, TextTools::toString(separator));
      unsigned int n = st.numberOfRemainingTokens();
      vector<T> v(n);
      for(unsigned int i = 0; i < n; i++)
      {
        v[i] = TextTools::fromString<T>(st.nextToken());
      }
      return v;
    }

    /**
     * @brief Get a vector.
     *
     * Similar to getVectorParameter, but dedicated to numerical values.
     * It allows the possibility to set range of values, which will be incremented by 1 (like the : operator in R).
     *
     * @param parameterName    The name of the corresponding parameter.
     * @param params           The attribute map where options may be found.
     * @param separator        The character used to delimit values.
     * @param rangeOperator    The character used to delimit ranges (the + 1 operator must be available for T).
     * @param defaultValue     The default value to use if the parameter is not found.
     * @param suffix           A suffix to be applied to the parameter name.
     * @param suffixIsOptional Tell if the suffix is absolutely required.
     * @param warn             Tell if a warning must be sent in case the parameter is not found.
     * @return The corresponding value.
     */
    template<class T> static vector<T> getVectorParameter(
      const string & parameterName,
      map<string, string> & params,
      char separator,
      char rangeOperator,
      const string & defaultValue,
      const string & suffix = "",
      bool suffixIsOptional = true,
      bool warn = true)
    {
      string s = getStringParameter(parameterName, params, defaultValue, suffix, suffixIsOptional, warn);
      StringTokenizer st(s, TextTools::toString(separator));
      unsigned int n = st.numberOfRemainingTokens();
      vector<T> v;
      for(unsigned int i = 0; i < n; i++)
      {
        string s = st.nextToken();
        string::size_type i = s.find(rangeOperator);
        if(i == string::npos)
          v.push_back(TextTools::fromString<T>(s));
        else
        {
          T d1 = TextTools::fromString<T>(s.substr(0, i));
          T d2 = TextTools::fromString<T>(s.substr(i+1));
          for(T j = d1; j < d2; j++)
          {
            v.push_back(j);
          }
          v.push_back(d2);
        }
      }
      return v;
    }
   
    /**
     * @name Output methods.
     *
     * @{
     */
    
    /**
     * @brief Print a message.
     *
     * @param text The text of the message.
     */
    static void displayMessage(const string & text);
    
    /**
     * @brief Print an error message.
     *
     * @param text The text of the message.
     */
    static void displayError(const string & text);
    
    /**
     * @brief Print a warning message.
     *
     * @param text The text of the message.
     */
    static void displayWarning(const string & text);
    
    /**
     * @brief Print a task message.
     *
     * Display the message and flush the buffer, but do not end the current line.
     *
     * @param text The text of the message.
     * @param eof  Insert a carriage return after displaying the message.
     */
    static void displayTask(const string & text, bool eof = false);
    
    /**
     * @brief Print a task ended message.
     *
     * Print "Done." and go to next line.
     */
    static void displayTaskDone();
    
    /**
     * @brief Print a result message.
     *
     * Result will be alined to 30 character from the begining of the message.
     * ex: text = "Here is what you get:" and result = "THAT" gives
     * "Here is what you get:          THAT".
     *    
     * @param text   The text of the message.
     * @param result The result.
     */
    template<class T>
    static void displayResult(const string & text, const T & result)
    {
      displayMessage(TextTools::resizeRight(text, (unsigned int) (terminalWidth * terminalSplit - 1), '.') + ": " + TextTools::toString<T>(result));
    }

    /**
     * @brief Display a gauge.
     *
     * Show progress status.
     * @code
     * for(unsigned int i = 0; i < 1000; i++)
     * {
     *   ApplicationTools::displayGauge(i, 999, '*');
     *   //Perform time consuming task...
     * }
     * @endcode
     * will result in something like:
     * @verbatim
     * [************************************]
     * @endverbatim
     * 
     * @param iter   The current iteration number.
     * @param total  The total number of iteration.
     * @param symbol The character to display in the gauge.
     * @param mes    A message to print before de gauge.
     */
    static void displayGauge(unsigned int iter, unsigned int total, char symbol='>', string mes="");

    /** @} */

    /**
     * @brief Starts the timer.
     */
    static void startTimer()
    {
      time(&startTime);
    }

    /**
     * @brief Display the current timer value to the 'message' stream.
     *
     * @param msg Message to display before time.
     */
    static void displayTime(const string & msg);
 
    /**
     * @brief Get the current timer value.
     *
     * @return The number of seconds from when timer was started.
     */
    static double getTime();
};

} //end of namespace bpp.

#endif  //_APPLICATIONTOOLS_H_

