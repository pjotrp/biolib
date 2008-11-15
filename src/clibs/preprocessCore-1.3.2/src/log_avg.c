/************************************************************************
 **
 ** log_avg.c
 **
 ** Copyright (C) 2003-2007 Ben Bolstad
 **
 ** created by: B. M. Bolstad   <bolstad@stat.berkeley.edu>
 ** created on: Feb 6, 2003  (but based on earlier work from Nov 2002)
 **
 ** last modified: Feb 6, 2003
 **
 ** License: GPL V2 or later (same as the rest of the Affy package)
 **
 ** General discussion
 **
 ** Implement log2 average pm summarization, with or without normalization
 **
 ** Feb 6, 2002 - Initial version of this summarization method
 ** Jul 23, 2003 - parameter for storing SE added (not yet implemented)
 ** Oct 5, 2003 - method of adding parameters. 
 ** May 19, 2007 - branch out of affyPLM into a new package preprocessCore, then restructure the code. Add doxygen style documentation
 ** Sep 19, 2007 - add LogAverage_noSE
 **
 ************************************************************************/

#include "log_avg.h"
#include "qnorm.h"

#include <R.h> 
#include <Rdefines.h>
#include <Rmath.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/***************************************************************************
 **
 ** double LogAvg(double *x, int length)
 **
 ** double *x - a vector of PM intensities 
 ** int length - length of *x
 **
 ** take the log2 of the average of PM intensities.
 **
 ***************************************************************************/

static double LogAvg(double *x, int length){
  int i;
  double sum = 0.0;
  double mean = 0.0;

  for (i=0; i < length; i++){
    sum = sum + x[i];
  }
  
  mean = sum/(double)length;
  
  mean = log(mean)/log(2.0);

  return (mean);    
}

/***************************************************************************
 ** 
 ** void averagelog(double *data, int rows, int cols, double *results, double *resultsSE)
 **
 ** aim: given a data matrix of probe intensities, compute average of log2 values in column wise manner 
 **      
 **
 ** double *data - Probe intensity matrix
 ** int rows - number of rows in matrix *data (probes)
 ** int cols - number of cols in matrix *data (chips)
 ** int *cur_rows - indicies of rows corresponding to current probeset
 ** double *results - already allocated location to store expression measures (cols length)
 ** int nprobes - number of probes in current probeset.
 **
 ***************************************************************************/


void logaverage(double *data, int rows, int cols, double *results, double *resultsSE){
  int i,j;
  double *z = Calloc(rows,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < rows; i++){
      z[i] = data[j*rows + i];
    }
    results[j] = LogAvg(z,rows);
    resultsSE[j] = R_NaReal;
  } 
}




/***************************************************************************
 **
 ** double LogAverage(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes)
 **
 ** aim: given a data matrix of probe intensities, and a list of rows in the matrix 
 **      corresponding to a single probeset, compute average log2 expression measure. 
 **      Note that data is a probes by chips matrix.
 **
 ** double *data - Probe intensity matrix
 ** int rows - number of rows in matrix *data (probes)
 ** int cols - number of cols in matrix *data (chips)
 ** int *cur_rows - indicies of rows corresponding to current probeset
 ** double *results - already allocated location to store expression measures (cols length)
 ** int nprobes - number of probes in current probeset.
 **
 ***************************************************************************/

/*! \brief Given a data matrix of probe intensities, and a list of rows in the matrix 
 *      corresponding to a single probeset, compute log2 average expression measure. 
 *      Note that data is a probes by chips matrix. Also compute SE estimates
 *
 * @param data a matrix containing data stored column-wise stored in rows*cols length of memory
 * @param rows the number of rows in the matrix 
 * @param cols the number of columns in the matrix
 * @param cur_rows a vector containing row indices to use
 * @param results pre-allocated space to store output log2 averages. Should be of length cols
 * @param nprobes number of probes in current set
 * @param resultsSE pre-allocated space to store SE of log2 averages. Should be of length cols
 *
 *  
 */
void LogAverage(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes, double *resultsSE){
  int i,j;
  double *z = Calloc(nprobes*cols,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[j*nprobes + i] = data[j*rows + cur_rows[i]];  
    }
  } 
  
  for (j=0; j < cols; j++){
    results[j] = LogAvg(&z[j*nprobes],nprobes);
    resultsSE[j] = R_NaReal;
  }
  Free(z);
}


void LogAverage_noSE(double *data, int rows, int cols, int *cur_rows, double *results, int nprobes){
  int i,j;
  double *z = Calloc(nprobes*cols,double);

  for (j = 0; j < cols; j++){
    for (i =0; i < nprobes; i++){
      z[j*nprobes + i] = data[j*rows + cur_rows[i]];  
    }
  } 
  
  for (j=0; j < cols; j++){
    results[j] = LogAvg(&z[j*nprobes],nprobes);
  }
  Free(z);
}

